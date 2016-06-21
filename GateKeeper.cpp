#include "stdafx.h"

#include "GateKeeper.h"
#include "pEpCOMServerAdapter.h"

using namespace std;

namespace pEp {

    const LPCTSTR GateKeeper::plugin_reg_path = _T("Software\\Microsoft\\Office\\Outlook\\Addins\\pEp");
    const LPCTSTR GateKeeper::plugin_reg_value_name = _T("LoadBehavior");
    const LPCTSTR GateKeeper::updater_reg_path = _T("Software\\pEp\\Updater";)

    const time_t GateKeeper::cycle = 7200;   // 7200 sec is 2 h
    const DWORD GateKeeper::waiting = 10000; // 10000 ms is 10 sec

    GateKeeper::GateKeeper(CpEpCOMServerAdapterModule * const self)
        : _self(self), now(time(NULL)), next(now + time_diff()), hkUpdater(NULL), internet(NULL)
    {
        LONG lResult = RegOpenCurrentUser(KEY_READ, &cu);
        assert(lResult == ERROR_SUCCESS);
        if (lResult == ERROR_SUCCESS)
            cu_open = true;
        else
            cu_open = false;

        if (cu_open) {
            LONG lResult = RegOpenKeyEx(cu, updater_reg_path, 0, KEY_READ, &hkUpdater);
            assert(lResult == ERROR_SUCCESS);
            if (lResult != ERROR_SUCCESS)
                return;
        }
    }
    
    GateKeeper::~GateKeeper()
    {
        if (cu_open) {
            if (hkUpdater)
                RegCloseKey(hkUpdater);
            RegCloseKey(cu);
        }
    }

    time_t GateKeeper::time_diff()
    {
        try {
            static random_device rd;
            static mt19937 gen(rd());

            uniform_int_distribution<time_t> dist(0, cycle);

            return dist(gen);
        }
        catch (exception&) {
            assert(0);
            return 0;
        }
    }

    void GateKeeper::keep()
    {
        if (!cu_open)
            return;

        while (1) {
            keep_plugin();

            now = time(NULL);
            assert(now != -1);

            if (now > next) {
                next = now + GateKeeper::cycle;
                keep_updated();
            }

            Sleep(waiting);
        }
    }

    void GateKeeper::keep_plugin()
    {
        while (!_self->m_bComInitialized)
            Sleep(1);

        MessageBox(NULL, _T("test"), _T("keep_plugin"), MB_ICONINFORMATION | MB_TOPMOST);

        DWORD value;
        DWORD size;

        LONG lResult = RegGetValue(cu, plugin_reg_path, plugin_reg_value_name, RRF_RT_REG_DWORD, NULL, &value, &size);
        if (lResult != ERROR_SUCCESS)
            return;

        if (value != 3) {
            lResult = RegSetValue(cu, plugin_reg_path, RRF_RT_REG_DWORD, plugin_reg_value_name, 3);
            assert(lResult == ERROR_SUCCESS);
        }
    }

    string GateKeeper::update_key()
    {
        static string key;

        if (key.length() == 0) {
            HRSRC res = FindResource(_self->hModule(), MAKEINTRESOURCE(IRD_UPDATEKEY), RT_RCDATA);
            assert(res);
            if (!res)
                throw runtime_error("FindResource: IRD_UPDATEKEY");

            HGLOBAL hRes = LoadResource(_self->hModule(), res);
            assert(hRes);
            if (!hRes)
                throw runtime_error("LoadResource: IRD_UPDATEKEY");

            key = string((char *)LockResource(hRes), SizeofResource(_self->hModule(), res));
            UnlockResource(hRes);
        }

        return key;
    }

    GateKeeper::product_list& GateKeeper::registered_products()
    {
        static product_list products;

        // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724872(v=vs.85).aspx
        static TCHAR value_name[16384];
        DWORD value_name_size;
        static TCHAR value[L_MAX_URL_LENGTH + 1];
        DWORD value_size;

        products.empty();

        LONG lResult = ERROR_SUCCESS;
        for (DWORD i = 0; lResult == ERROR_SUCCESS; i++) {
            value_size = L_MAX_URL_LENGTH + 1;
            lResult = RegEnumValue(hkUpdater, 0, value_name, &value_name_size, NULL, NULL, (LPBYTE) value, &value_size);
            if (lResult == ERROR_SUCCESS)
                products.push_back({ value_name, value });
        }

        return products;
    }

    string GateKeeper::handshake(HINTERNET hUrl)
    {
        string key;

        // handshake key
        
        return key;
    }

    void GateKeeper::update_product(product p, DWORD context)
    {
        HINTERNET hUrl = InternetOpenUrl(internet, p.second.c_str(), NULL, 0,
                INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE, context);
        if (hUrl == NULL)
            return;

        // update
        PCTSTR rgpszAcceptTypes[] = { _T("text/plain"), NULL };
        HINTERNET hRequest = HttpOpenRequest(hUrl, NULL, _T("challenge"), NULL, NULL, rgpszAcceptTypes, INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE, context);


        InternetCloseHandle(hUrl);
    }

    void GateKeeper::keep_updated()
    {
        return; // disabled for now

        internet = InternetOpen(_T("pEp"), INTERNET_OPEN_TYPE_PROXY, NULL, NULL, 0);

        product_list& products = registered_products();
        DWORD context = 0;
        for (auto i = products.begin(); i != products.end(); i++) {
            update_product(*i, context++);
        }

        InternetCloseHandle(internet);
        internet = NULL;
    }

} // namespace pEp
