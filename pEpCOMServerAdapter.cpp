// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "pEpCOMServerAdapter_i.h"
#include "xdlldata.h"

#include "GateKeeper.h"

using namespace ATL;
using namespace std;

class CpEpCOMServerAdapterModule : public ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule >
{
public:
    HRESULT PreMessageLoop(int nShowCmd)
    {
        ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule >::PreMessageLoop(nShowCmd);

        gatekeeper_thread = new thread(gatekeeper, this);
        gatekeeper_thread->detach();
    }

	DECLARE_LIBID(LIBID_pEpCOMServerAdapterLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PEPCOMSERVERADAPTER, "{B3480081-82C0-4EE4-9AA1-3F513C9D78DD}")

protected:
    static void gatekeeper(CpEpCOMServerAdapterModule * const self);

private:
    thread *gatekeeper_thread;
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

