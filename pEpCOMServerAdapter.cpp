// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "xdlldata.h"

#include "GateKeeper.h"
#include "pEpCOMServerAdapter.h"
#include "LocalJSONAdapter.h"

using namespace ATL;
using namespace std;

void CpEpCOMServerAdapterModule::gatekeeper(CpEpCOMServerAdapterModule * self)
{
    pEp::GateKeeper keeper(self);
    keeper.keep();
}

CpEpCOMServerAdapterModule _AtlModule;

//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR lpCmdLine, int nShowCmd)
{
    _AtlModule.hModule(hInstance);
    _AtlModule.start_gatekeeper();

    PEP_SESSION first_session;
    PEP_STATUS status = ::init(&first_session, NULL, NULL);

    LocalJSONAdapter* ljs = nullptr;
    SessionRegistry* sr = nullptr;

    if (!boost::algorithm::iequals(lpCmdLine, "/regserver"))
        ljs= &LocalJSONAdapter::createInstance();
    
    if (ljs)
        ljs->startup();

    auto rv = _AtlModule.WinMain(nShowCmd);

    if (ljs)
        ljs->shutdown_now();

    ::release(first_session);
    return rv;
}
