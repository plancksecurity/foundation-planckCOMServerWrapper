#pragma once
#include "stdafx.h"
#include "resource.h"

using namespace ATL;

#define WM_PEP_NOTIFICATION WM_USER + 23

class CMainWindow :
    public CWindowImpl<CMainWindow>
{
    bool _schedule_updates;

public:
    CMainWindow() :
        _schedule_updates(true), CWindowImpl<CMainWindow>() { }

    DECLARE_WND_CLASS(_T("pEpCOMServerAdapterMainWndClass"))
    BEGIN_MSG_MAP(CMainWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_PEP_NOTIFICATION, OnNotification)
        MESSAGE_HANDLER(WM_MENUCOMMAND, OnMenuCommand)
    END_MSG_MAP()

    LRESULT OnCreate(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnNotification(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnMenuCommand(UINT /*nMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

    typedef std::basic_string<TCHAR> tstring;
    static tstring r(UINT resid);
    void ShowNotificationInfo(tstring title, tstring text);
};
