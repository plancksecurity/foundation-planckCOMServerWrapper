#include "stdafx.h"
#include "CMainWindow.h"
#include "GateKeeper.h"

static const GUID nidGUID =
{ 0xa4dbdbe1, 0x4051, 0x4d89, { 0xb1, 0x17, 0x62, 0x82, 0x18, 0x5a, 0x61, 0x5c } };

CMainWindow::CMainWindow() :
    _schedule_updates(true), CWindowImpl<CMainWindow>()
{
    ULONG ulNumLanguages = 0;
    PZZWSTR pwszLanguagesBuffer = NULL;
    ULONG pcchLanguagesBuffer = 0;
    BOOL bResult = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &ulNumLanguages, NULL, &pcchLanguagesBuffer);
    assert(bResult);
    pwszLanguagesBuffer = new WCHAR[pcchLanguagesBuffer];
    bResult = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &ulNumLanguages, pwszLanguagesBuffer, &pcchLanguagesBuffer);
    assert(bResult);
    bResult = SetProcessPreferredUILanguages(MUI_LANGUAGE_NAME, pwszLanguagesBuffer, &ulNumLanguages);
    assert(bResult);
    delete[] pwszLanguagesBuffer;
}

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
    StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), r(IDS_PROJNAME).c_str());
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

LRESULT CMainWindow::OnNotification(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    auto event = LOWORD(lParam);
    auto icon_id = HIWORD(lParam);
    auto x = GET_X_LPARAM(wParam);
    auto y = GET_Y_LPARAM(wParam);

    HMENU menuContext;
    HMENU _menuContext = NULL;

    MENUINFO info;
    BOOL enabled;

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

        enabled = pEp::GateKeeper::gatekeeper()->update_enabled();
        CheckMenuItem(_menuContext, ID_POPUP_SCHEDULEUPDATES, enabled ? MF_CHECKED : MF_UNCHECKED);

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

static const auto UPDATE_NOW = 0;
static const auto SCHEDULE_UPDATES = 2;

LRESULT CMainWindow::OnMenuCommand(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    auto index = wParam;
    HMENU hMenu = (HMENU)lParam;
    BOOL enabled;

    switch (index) {
    case UPDATE_NOW:
        ShowNotificationInfo(r(IDS_UPDATESTITLE), r(IDS_UPDATESTEXT));
        pEp::GateKeeper::gatekeeper()->update_now();
        bHandled = true;
        break;

    case SCHEDULE_UPDATES:
        enabled = !pEp::GateKeeper::gatekeeper()->update_enabled();
        if (enabled)
            pEp::GateKeeper::gatekeeper()->enable_update();
        else
            pEp::GateKeeper::gatekeeper()->disable_update();
        CheckMenuItem(hMenu, ID_POPUP_SCHEDULEUPDATES, enabled ? MF_CHECKED : MF_UNCHECKED);
        bHandled = true;
        break;

    default:
        bHandled = false;
    }
    return S_OK;
}

CMainWindow::tstring CMainWindow::r(UINT resid)
{
    LPCTSTR rstr;
    size_t rsize = LoadString(GetModuleHandle(NULL), resid, (LPWSTR) &rstr, 0);
    tstring str = tstring(rstr, rsize);
    return str;
}

void CMainWindow::ShowNotificationInfo(tstring title, tstring text)
{
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.uFlags = NIF_GUID | NIF_MESSAGE | NIF_INFO;
    nid.dwInfoFlags = NIIF_LARGE_ICON;
    nid.hWnd = m_hWnd;
    nid.guidItem = nidGUID;
    nid.hBalloonIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOGO));
    StringCchCopy(nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle), title.substr(0, ARRAYSIZE(nid.szInfoTitle)-1).c_str());
    StringCchCopy(nid.szInfo, ARRAYSIZE(nid.szInfo), text.substr(0, ARRAYSIZE(nid.szInfo) - 1).c_str());
    nid.uCallbackMessage = WM_PEP_NOTIFICATION;
    Shell_NotifyIcon(NIM_MODIFY, &nid);
}
