// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "pEpCOMServerAdapter_i.h"
#include "xdlldata.h"


using namespace ATL;
using namespace std;

class CpEpCOMServerAdapterModule;

static class GateKeeper {
public:
    static const time_t cycle = 7200;   // 7200 sec is 2 h
    static const DWORD waiting = 10000; // 10000 ms is 10 sec

    static time_t time_diff()
    {
        try {
            static random_device rd;
            static mt19937 gen(rd());

            uniform_int_distribution<time_t> dist(0, cycle);

            return dist(gen);
        }
        catch (exception& e) {
            assert(0);
            return 0;
        }
    }

    GateKeeper(CpEpCOMServerAdapterModule * const self) : _self(self), now(time(NULL)), next(now + time_diff())
    {
        LONG lResult = RegOpenCurrentUser(KEY_READ, &cu);
        assert(lResult == ERROR_SUCCESS);
    }

    ~GateKeeper()
    {
        RegCloseKey(cu);
    }

    void keep();

    void keep_plugin();
    void keep_updated();

protected:
    static const LPCTSTR plugin_reg_path;
    static const LPCTSTR plugin_reg_value_name;

private:
    time_t now;
    time_t next;
    HKEY cu;

    CpEpCOMServerAdapterModule * const _self;
};

const LPCTSTR GateKeeper::plugin_reg_path = _T("Software\\Microsoft\\Office\\Outlook\\Addins\\pEp");
const LPCTSTR GateKeeper::plugin_reg_value_name = _T("LoadBehavior");

void GateKeeper::keep()
{
    while (1) {
        keep_plugin();

        now = time(NULL);
        assert(now != -1);
        
        if (now > next) {
            next = now + GateKeeper::cycle;
            keep_updated();
        }

        Sleep(10000);
    }
}

void GateKeeper::keep_plugin()
{
    DWORD value;
    DWORD size;
    LONG lResult = RegGetValue(cu, plugin_reg_path, plugin_reg_value_name, RRF_RT_REG_DWORD, NULL, &value, &size);

    assert(lResult == ERROR_SUCCESS);
    if (lResult != ERROR_SUCCESS)
        return;

    if (value != 3) {
        lResult = RegSetValue(cu, plugin_reg_path, RRF_RT_REG_DWORD, plugin_reg_value_name, 3);
        assert(lResult == ERROR_SUCCESS);
    }
}

void GateKeeper::keep_updated()
{

}

class CpEpCOMServerAdapterModule : public ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule >
{
public:
    CpEpCOMServerAdapterModule() : ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule >(), gatekeeper_thread(NULL)
    {
        gatekeeper_thread = new thread(gatekeeper, this);
        gatekeeper_thread->detach();
    }

	DECLARE_LIBID(LIBID_pEpCOMServerAdapterLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PEPCOMSERVERADAPTER, "{B3480081-82C0-4EE4-9AA1-3F513C9D78DD}")

private:
    thread *gatekeeper_thread;

protected:
    static void gatekeeper(CpEpCOMServerAdapterModule * const self);
};

void CpEpCOMServerAdapterModule::gatekeeper(CpEpCOMServerAdapterModule * const self)
{
    GateKeeper keeper(self);
    keeper.keep();
}

CpEpCOMServerAdapterModule _AtlModule;

//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

