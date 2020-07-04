// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "xdlldata.h"

#include "GateKeeper.h"
#include "pEpCOMServerAdapter.h"
#include "LocalJSONAdapter.h"
#include "CMainWindow.h"

using namespace ATL;
using namespace std;

#ifndef NDEBUG
// Stuff for the JSON server follows.
#include <boost/filesystem/path.hpp>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
std::string logfile = "";
#endif

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
#endif

    _AtlModule.hModule(hInstance);
    _AtlModule.start_gatekeeper();

    PEP_SESSION first_session;
    PEP_STATUS status = ::init(&first_session, NULL, NULL);

    if (!boost::algorithm::iequals(lpCmdLine, "/regserver")) {
        ljs = &LocalJSONAdapter::createInstance();
        ljs->startup(pEp::CallbackDispatcher::messageToSend);
        pEp::callback_dispatcher.add(JsonAdapter::messageToSend, JsonAdapter::notifyHandshake);
        auto mw = mainWindow.Create(HWND_MESSAGE);
        assert(mw);
    }

    auto rv = _AtlModule.WinMain(nShowCmd);

    if (ljs) {
        BOOL r = true;
        mainWindow.OnDestroy(0, 0, 0, r);
        pEp::callback_dispatcher.remove(JsonAdapter::messageToSend);
        ljs->shutdown_now();
    }

    ::release(first_session);
    ExitProcess(rv);
    return rv;
}
