// pEpCOMServerAdapter.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "xdlldata.h"

#include "GateKeeper.h"
#include "pEpCOMServerAdapter.h"

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
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    _AtlModule.hModule(hInstance);
    _AtlModule.start_gatekeeper();

    return _AtlModule.WinMain(nShowCmd);
}
