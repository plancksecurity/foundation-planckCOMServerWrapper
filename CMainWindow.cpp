#include "stdafx.h"
#include "CMainWindow.h"

static const GUID nidGUID =
{ 0xa4dbdbe1, 0x4051, 0x4d89, { 0xb1, 0x17, 0x62, 0x82, 0x18, 0x5a, 0x61, 0x5c } };

LRESULT CMainWindow::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
    // remove leftoff before creating a new one
    BOOL _b;
    OnDestroy(0, 0, 0, _b);

    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_GUID | NIF_MESSAGE;
    nid.hWnd = m_hWnd;
    nid.guidItem = nidGUID;
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), _T("p≡p Updates"));
    nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOGO));
    nid.uCallbackMessage = WM_PEP_NOTIFICATION;
    Shell_NotifyIcon(NIM_ADD, &nid);

    nid = {};
    nid.cbSize = sizeof(nid);
    nid.uVersion = NOTIFYICON_VERSION_4;
    Shell_NotifyIcon(NIM_SETVERSION, &nid);

    return S_OK;
}

LRESULT CMainWindow::OnDestroy(UINT, WPARAM, LPARAM, BOOL&)
{
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.uFlags = NIF_ICON | NIF_GUID;
    nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOGO));
    nid.guidItem = nidGUID;
    Shell_NotifyIcon(NIM_DELETE, &nid);

    return S_OK;
}

HMENU _menuContext = NULL;

LRESULT CMainWindow::OnNotification(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    auto event = LOWORD(lParam);
    auto icon_id = HIWORD(lParam);
    auto x = GET_X_LPARAM(wParam);
    auto y = GET_Y_LPARAM(wParam);

    HMENU menuContext;
    MENUINFO info;

    switch (event) {
    case WM_CONTEXTMENU:
    case WM_RBUTTONDOWN:
        menuContext = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_POPUPMENU));
        info = {};
        info.cbSize = sizeof(info);
        info.fMask = MIM_APPLYTOSUBMENUS | MIM_STYLE;
        info.dwStyle = MNS_AUTODISMISS | MNS_NOTIFYBYPOS;
        SetMenuInfo(menuContext, &info);
        _menuContext = GetSubMenu(menuContext, 0);
        SetForegroundWindow(m_hWnd); // this is utter nonsense, but required by TrackPopupMenuEx
        POINT point;
        GetCursorPos(&point);
        TrackPopupMenuEx(_menuContext, TPM_LEFTALIGN | TPM_BOTTOMALIGN, point.x, point.y, m_hWnd, NULL);
        PostMessage(WM_NULL, 0, 0); // this is utter nonsense, but required by TrackPopupMenuEx
        DestroyMenu(menuContext);
        bHandled = true;
        break;

    default:
        bHandled = false;
    }

    return S_OK;
}

static const auto UPDATE_NOW = 1;

LRESULT CMainWindow::OnMenuCommand(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    auto index = wParam;
    HMENU hMenu = (HMENU)lParam;

    switch (index) {
    case UPDATE_NOW:
        ::MessageBox(NULL, _T("update now"), _T("update now"), MB_ICONINFORMATION);
        bHandled = true;
        break;

    default:
        bHandled = false;
    }
    return S_OK;
}
