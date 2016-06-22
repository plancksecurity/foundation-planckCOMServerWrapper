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

    GateKeeper::GateKeeper(CpEpCOMServerAdapterModule * self)
        : _self(self), now(time(NULL)), next(now + time_diff()), hkUpdater(NULL), internet(NULL), hAES(NULL), hRSA(NULL)
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

    BCRYPT_KEY_HANDLE GateKeeper::delivery_key()
    {
        aeskey_t key;

        static random_device rd;
        static mt19937 gen(rd());

        uniform_int_distribution<time_t> dist(0, UINT64_MAX);

        key.qw_key[0] = dist(gen);
        key.qw_key[1] = dist(gen);

        BCRYPT_KEY_HANDLE hKey;
        NTSTATUS status = BCryptGenerateSymmetricKey(hAES, &hKey, NULL, 0, (PUCHAR) &key, (ULONG) sizeof(aeskey_t), 0);
        assert(status == 0);
        if (status)
            throw runtime_error("BCryptGenerateSymmetricKey");

        return hKey;
    }

    string GateKeeper::wrapped_delivery_key(BCRYPT_KEY_HANDLE hDeliveryKey)
    {
        string result;

        BCRYPT_KEY_HANDLE hUpdateKey;
        string _update_key = update_key();

        NTSTATUS status = BCryptImportKeyPair(hRSA, NULL, BCRYPT_RSAPUBLIC_BLOB, &hUpdateKey,
                (PUCHAR) _update_key.data(), _update_key.size(), 0);
        if (status)
            throw runtime_error("BCryptImportKeyPair: update_key");

        aeskey_t _delivery_key;
        ULONG copied;
        status = BCryptExportKey(hDeliveryKey, NULL, BCRYPT_KEY_DATA_BLOB, (PUCHAR) &_delivery_key, sizeof(aeskey_t), &copied, 0);
        if (status)
            throw runtime_error("BCryptExportKey: delivery_key");

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<time_t> dist(0, UINT64_MAX);
        uint64_t r[32];
        for (int i = 0; i < 32; i++)
            r[i] = dist(gen);

        BCRYPT_OAEP_PADDING_INFO pi;
        memset(&pi, 0, sizeof(BCRYPT_OAEP_PADDING_INFO));
        pi.pszAlgId = BCRYPT_SHA256_ALGORITHM;
        pi.pbLabel = (PUCHAR) r;
        pi.cbLabel = sizeof(r);

        ULONG result_size;
        PUCHAR _result = NULL;
        status = BCryptEncrypt(hUpdateKey, (PUCHAR) &_delivery_key, sizeof(aeskey_t), &pi, NULL, 0, NULL, 0, &result_size, BCRYPT_PAD_OAEP);
        if (status) {
            BCryptDestroyKey(hUpdateKey);
            throw runtime_error("BCryptEncrypt: calculating result size");
        }

        _result = new UCHAR[result_size];
        status = BCryptEncrypt(hUpdateKey, (PUCHAR) &_delivery_key, sizeof(aeskey_t), &pi, NULL, 0, _result, result_size, &copied, BCRYPT_PAD_OAEP);
        if (status) {
            BCryptDestroyKey(hUpdateKey);
            delete[] _result;
            throw runtime_error("BCryptEncrypt: encrypting using update_key");
        }

        BCryptDestroyKey(hUpdateKey);

        stringstream s;
        s << hex << setw(2) << setfill('0');
        for (ULONG i = 0; i < copied; i++)
            s << (int) _result[i];
        delete[] _result;
        s >> result;

        return result;
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

        NTSTATUS status = BCryptOpenAlgorithmProvider(&hAES, BCRYPT_AES_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;

        status = BCryptOpenAlgorithmProvider(&hRSA, BCRYPT_RSA_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;

        internet = InternetOpen(_T("pEp"), INTERNET_OPEN_TYPE_PROXY, NULL, NULL, 0);
        if (!internet)
            goto closing;

        product_list& products = registered_products();
        DWORD context = 0;
        for (auto i = products.begin(); i != products.end(); i++) {
            update_product(*i, context++);
        }

    closing:
        if (internet)
            InternetCloseHandle(internet);
        if (hAES)
            BCryptCloseAlgorithmProvider(hAES, 0);
        if (hRSA)
            BCryptCloseAlgorithmProvider(hRSA, 0);
        internet = NULL;
        hAES = NULL;
        hRSA = NULL;
    }

} // namespace pEp
