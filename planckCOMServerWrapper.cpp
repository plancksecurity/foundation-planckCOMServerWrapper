// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "xdlldata.h"

#include "GateKeeper.h"
#include "planckCOMServerWrapper.h"
#include "LocalJSONAdapter.h"
#include "CMainWindow.h"
#include "LocalProvisioning.h"
#include "MediaKeyManager.h"
#include "ExtraKeyManager.h"
#include <iostream>
#include <sddl.h>
#include <Lmcons.h>


using namespace ATL;
using namespace std;

#ifndef NDEBUG
// Stuff for the JSON server follows.
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
std::string logfile = "";
#endif

void init_provisioning_log();

// Check that this is the only instance.
// It uses a named mutex to see if one instance of this binary is being executed
// by the current user. 
namespace CheckInstance
{
    HANDLE hMutexHandle = nullptr;

    std::string getCurrentUserName()
    {
        CHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;

        if (!GetUserNameA(username, &username_len))
            return "";
        else
            return username;
    }

    std::string getSID()
    {
        std::string ret;
        std::string user_name = getCurrentUserName();
        LPCSTR username = user_name.c_str();

        PSID user_sid;
        DWORD sid_size = SECURITY_MAX_SID_SIZE;
        CHAR domain_name[256];
        DWORD domain_size = 256;
        SID_NAME_USE sid_use;

        user_sid = (PSID)GlobalAlloc(GPTR, sid_size);
        if (!LookupAccountNameA(NULL, username, user_sid, &sid_size, domain_name, &domain_size, &sid_use))
            return user_name;

        CHAR* sid_string;
        if (!ConvertSidToStringSidA(user_sid, &sid_string))
        {
            GlobalFree(user_sid);
            return user_name;
        }

        ret = sid_string;

        GlobalFree(user_sid);
        LocalFree(sid_string);

        return ret;
    }

    // returns true if this is the first instance of this adapter.
    // one adapter is allowed per user.
    bool isFirst()
    {
        std::stringstream instance_name;
        instance_name << "pEpComServerAdapter." << getSID();
        // create a mutex with unique name for every user
        hMutexHandle = CreateMutexA(NULL, TRUE, instance_name.str().c_str());
        if (GetLastError() == ERROR_ALREADY_EXISTS) // a mutex with the same name exists?
            return false;
        else
            return true;
    }

    void release() noexcept
    {
        if (hMutexHandle)
        {
            ReleaseMutex(hMutexHandle);
            CloseHandle(hMutexHandle);
        }
    }

};


void CpEpCOMServerAdapterModule::gatekeeper(CpEpCOMServerAdapterModule * self)
{
    pEp::GateKeeper keeper(self);
    keeper.keep();
}

CpEpCOMServerAdapterModule _AtlModule;
LocalJSONAdapter* ljs = nullptr;
CMainWindow mainWindow;

extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR lpCmdLine, int nShowCmd)
{
#ifndef NDEBUG
    std::ios::sync_with_stdio(false);

    if (!CheckInstance::isFirst())
        return 0;

    // Command line options and console output are for debug only.

    // Some Windows acrobatics so we can use this even with a command line
    // and get some output onto the console.
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        FILE *f;
        freopen_s(&f, "conout$", "w", stdout);
        freopen_s(&f, "conout$", "w", stderr);
    }

    po::options_description desc("Program options for the JSON Server Adapter");
    desc.add_options()
        ("help,h", "print this help messages")
        ("debug,d", "debug,d ignored, only works in JSON mini adapter")
        ("logfile,l", po::value<std::string>(&logfile)->default_value(logfile),
            "Name of the logfile. Can be \"stderr\" for log to stderr or empty for no log.")
    ;

    po::variables_map vm;
    try {
        std::vector<std::wstring> args = po::split_winmain(lpCmdLine);
        po::store(po::wcommand_line_parser(args).options(desc).run(), vm);
        po::notify(vm);
    } catch (const po::error& e) {
        std::cerr << "Cannot parse command line: " << e.what() << "\n\n" << desc << std::endl;
        return 2;
    }

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (logfile.empty()) {
        Logger::setDefaultTarget(Logger::Target::None);
    } else if (logfile == "stderr") {
        Logger::setDefaultTarget(Logger::Target::Console);
    } else {
        Logger::setDefaultTarget(Logger::Target::File);
    }

    Logger::start("JsonAdapter", logfile);
#else
    // Start the logger even for non-debug builds, see JSON-187.
    Logger::setDefaultTarget(Logger::Target::None);
    Logger::start("JsonAdapter", "");
#endif

    _AtlModule.hModule(hInstance);
    _AtlModule.start_gatekeeper();

    // Provisioning
    init_provisioning_log();
    pEp::LocalProvisioning provisioning;
    provisioning.Run();

    PEP_SESSION first_session;
    PEP_STATUS status = ::init(&first_session, NULL, NULL, pEp::Adapter::_ensure_passphrase);

    if (!boost::algorithm::iequals(lpCmdLine, "/regserver")) {
        ljs = &LocalJSONAdapter::createInstance();
        ljs->startup(pEp::CallbackDispatcher::messageToSend);
        pEp::callback_dispatcher.add(JsonAdapter::messageToSend, JsonAdapter::notifyHandshake);
        auto mw = mainWindow.Create(HWND_MESSAGE);
        assert(mw);
    }

    // Import new media keys
    {
        pEp::MediaKeyManager media_key_manager(first_session);
        media_key_manager.ImportKeys();
    }

    // Import extra keys
    {
        pEp::ExtraKeyManager extra_key_manager(first_session);
        extra_key_manager.ImportKeys();
    }

    auto rv = _AtlModule.WinMain(nShowCmd);

    if (ljs) {
        BOOL r = true;
        mainWindow.OnDestroy(0, 0, 0, r);
        pEp::callback_dispatcher.remove(JsonAdapter::messageToSend);
        ljs->shutdown_now();
    }

    CheckInstance::release();
    ::release(first_session);
    ExitProcess(rv);
    return rv;
}



void init_provisioning_log()
{
    static bool initialized = false;
    if (initialized)
        return;

    static const std::string COMMON_FMT("[%TimeStamp%][%Function%]:  %Message%");
    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

    // Output message to file, rotates when file reached 1mb or at midnight every day. Each log file
    // is capped at 1mb and total is 20mb
    boost::filesystem::path user_dir(SignedPackage::pEp_locations.at("PER_USER_DIRECTORY"));
    boost::filesystem::path log_path = user_dir / "Logs" / "provisioning_log%3N.txt";
    boost::log::add_file_log(
        boost::log::keywords::file_name = log_path.c_str(),
        boost::log::keywords::rotation_size = 1 * 1024 * 1024,
        boost::log::keywords::max_size = 20 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format = COMMON_FMT,
        boost::log::keywords::auto_flush = true
    );

    boost::log::add_common_attributes();

    // Only output message with INFO or higher severity in Release
#ifndef _DEBUG
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info
    );
#endif

    initialized = true;
}
