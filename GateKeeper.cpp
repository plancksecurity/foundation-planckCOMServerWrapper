#include "stdafx.h"

#include "GateKeeper.h"
#include "planckCOMServerWrapper.h"
#include "CMainWindow.h"

using namespace std;

extern CMainWindow mainWindow;
auto r = CMainWindow::r;

// from https://msdn.microsoft.com/en-us/library/windows/desktop/dd388945(v=vs.85).aspx

struct PUBLIC_KEY_VALUES {
    BLOBHEADER blobheader;
    RSAPUBKEY rsapubkey;
    BYTE modulus[4096];
};

static void ReverseMemCopy(
    _Out_ BYTE       *pbDest,
    _In_  BYTE const *pbSource,
    _In_  DWORD       cb
)
{
    for (DWORD i = 0; i < cb; i++) {
        pbDest[cb - 1 - i] = pbSource[i];
    }
}

static NTSTATUS ImportRsaPublicKey(
    _In_ BCRYPT_ALG_HANDLE  hAlg,    // CNG provider
    _In_ PUBLIC_KEY_VALUES *pKey,    // Pointer to the RSAPUBKEY blob.
    _In_ BCRYPT_KEY_HANDLE *phKey    // Receives a handle the imported public key.
)
{
    NTSTATUS hr = 0;

    BYTE *pbPublicKey = NULL;
    DWORD cbKey = 0;

    // Layout of the RSA public key blob:

    //  +----------------------------------------------------------------+
    //  |     BCRYPT_RSAKEY_BLOB    | BE( dwExp ) |   BE( Modulus )      |
    //  +----------------------------------------------------------------+
    //
    //  sizeof(BCRYPT_RSAKEY_BLOB)       cbExp           cbModulus 
    //  <--------------------------><------------><---------------------->
    //
    //   BE = Big Endian Format                                                     

    DWORD cbModulus = (pKey->rsapubkey.bitlen + 7) / 8;
    DWORD dwExp = pKey->rsapubkey.pubexp;
    DWORD cbExp = (dwExp & 0xFF000000) ? 4 :
        (dwExp & 0x00FF0000) ? 3 :
        (dwExp & 0x0000FF00) ? 2 : 1;

    BCRYPT_RSAKEY_BLOB *pRsaBlob;
    PBYTE pbCurrent;

    if (!SUCCEEDED(hr = DWordAdd(cbModulus, sizeof(BCRYPT_RSAKEY_BLOB), &cbKey))) {
        goto cleanup;
    }

    cbKey += cbExp;

    pbPublicKey = (PBYTE)CoTaskMemAlloc(cbKey);
    if (pbPublicKey == NULL) {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    ZeroMemory(pbPublicKey, cbKey);
    pRsaBlob = (BCRYPT_RSAKEY_BLOB *)(pbPublicKey);

    //
    // Make the Public Key Blob Header
    //

    pRsaBlob->Magic = BCRYPT_RSAPUBLIC_MAGIC;
    pRsaBlob->BitLength = pKey->rsapubkey.bitlen;
    pRsaBlob->cbPublicExp = cbExp;
    pRsaBlob->cbModulus = cbModulus;
    pRsaBlob->cbPrime1 = 0;
    pRsaBlob->cbPrime2 = 0;

    pbCurrent = (PBYTE)(pRsaBlob + 1);

    //
    // Copy pubExp Big Endian 
    //

    ReverseMemCopy(pbCurrent, (PBYTE)&dwExp, cbExp);
    pbCurrent += cbExp;

    //
    // Copy Modulus Big Endian 
    //

    ReverseMemCopy(pbCurrent, pKey->modulus, cbModulus);

    //
    // Import the public key
    //

    hr = BCryptImportKeyPair(hAlg, NULL, BCRYPT_RSAPUBLIC_BLOB, phKey, (PUCHAR)pbPublicKey, cbKey, 0);

cleanup:
    CoTaskMemFree(pbPublicKey);
    return hr;
}

namespace pEp {
    const LPCTSTR GateKeeper::plugin_reg_path = _T("Software\\Microsoft\\Office\\Outlook\\Addins\\pEp");
    const LPCTSTR GateKeeper::plugin_reg_value_name = _T("LoadBehavior");
    const LPCTSTR GateKeeper::updater_reg_path = _T("Software\\planck\\Updater");

    const time_t GateKeeper::cycle = 7200;   // 7200 sec is 2 h
    const time_t GateKeeper::fraction = 10;  // first update is at 10% of cycle
    const DWORD GateKeeper::waiting = 10000; //  10 sec

    GateKeeper::GateKeeper(CpEpCOMServerAdapterModule * self)
        : _self(self), now(time(NULL)), next(now /*+ time_diff()*/), hkUpdater(NULL),
        internet(NULL), hAES(NULL), hRSA(NULL)
    {
        if (the_gatekeeper)
            throw runtime_error("second instance of GateKeeper was initialized");

        DeleteFile(get_lockFile().c_str());

        LONG lResult = RegOpenCurrentUser(KEY_READ, &cu);
        assert(lResult == ERROR_SUCCESS);
        if (lResult == ERROR_SUCCESS)
            cu_open = true;
        else
            cu_open = false;

        if (cu_open) {
            LONG lResult = RegOpenKeyEx(cu, updater_reg_path, 0, KEY_READ, &hkUpdater);
            if (lResult != ERROR_SUCCESS)
                RegCreateKeyEx(cu, updater_reg_path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hkUpdater, NULL);
        }

        the_gatekeeper = this;
    }

    GateKeeper::~GateKeeper()
    {
        the_gatekeeper = nullptr;

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

            uniform_int_distribution<time_t> dist(0, cycle / fraction);

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
                if (update_enabled() && Is_update_available())
                {
                    mainWindow.ShowNotificationInfo(r(IDS_NEWUPDATE_TITLE), r(IDS_NEWUPDATE_TEXT));
                }
            }

            Sleep(waiting);
        }
    }

    void GateKeeper::keep_plugin()
    {
        HKEY hkPluginStart = NULL;

        LONG lResult = RegOpenKeyEx(cu, plugin_reg_path, 0, KEY_WRITE, &hkPluginStart);
        if (lResult != ERROR_SUCCESS)
            return;

        DWORD v = 3;
        lResult = RegSetValueEx(hkPluginStart, plugin_reg_value_name, 0, REG_DWORD, (const BYTE *)&v, sizeof(DWORD));
        assert(lResult == ERROR_SUCCESS);

        RegCloseKey(hkPluginStart);
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

        uniform_int_distribution<int64_t> dist(0, UINT32_MAX);

        for (int i = 0; i < 8; i++)
            key.dw_key[i] = (uint32_t)dist(gen);

        BCRYPT_KEY_HANDLE hKey;

        NTSTATUS status = BCryptGenerateSymmetricKey(hAES, &hKey, NULL, 0, (PUCHAR)&key, (ULONG) sizeof(aeskey_t), 0);
        assert(status == 0);
        if (status)
            throw runtime_error("BCryptGenerateSymmetricKey");

#ifndef NDEBUG
        DWORD keylength = 0;
        ULONG copied = 0;
        status = BCryptGetProperty(hKey, BCRYPT_KEY_LENGTH, (PUCHAR)&keylength, sizeof(DWORD), &copied, 0);
        assert(keylength == 256);
#endif

        return hKey;
    }

    string GateKeeper::wrapped_delivery_key(BCRYPT_KEY_HANDLE hDeliveryKey)
    {
        string result;

        BCRYPT_KEY_HANDLE hUpdateKey = NULL;
        string _update_key = update_key();

        PCERT_PUBLIC_KEY_INFO uk = NULL;
        DWORD uk_size = 0;

        BOOL bResult = CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO,
            (const BYTE *)_update_key.data(), _update_key.size(), CRYPT_DECODE_ALLOC_FLAG, NULL, &uk, &uk_size);
        if (!bResult)
            throw runtime_error("CryptDecodeObjectEx: X509_PUBLIC_KEY_INFO");

        PUBLIC_KEY_VALUES *_uk = NULL;
        DWORD _uk_size = 0;

        bResult = CryptDecodeObjectEx(X509_ASN_ENCODING, RSA_CSP_PUBLICKEYBLOB,
            uk->PublicKey.pbData, uk->PublicKey.cbData, CRYPT_DECODE_ALLOC_FLAG, NULL, &_uk, &_uk_size);
        LocalFree(uk);
        if (!bResult)
            throw runtime_error("CryptDecodeObjectEx: X509_PUBLIC_KEY_INFO");

        HRESULT hResult = ImportRsaPublicKey(hRSA, _uk, &hUpdateKey);
        LocalFree(_uk);
        if (!hUpdateKey)
            throw runtime_error("ImportRsaPublicKey");

        ULONG psize;
        NTSTATUS status = BCryptGetProperty(hUpdateKey, BCRYPT_ALGORITHM_NAME, NULL, 0, &psize, 0);
        char *prop = new char[psize];
        TCHAR *_prop = (TCHAR *)prop;
        status = BCryptGetProperty(hUpdateKey, BCRYPT_ALGORITHM_NAME, (PUCHAR)prop, psize, &psize, 0);
        if (status)
            throw runtime_error("BCryptGetProperty: BCRYPT_ALGORITHM_NAME");

        ULONG export_size;
        status = BCryptExportKey(hDeliveryKey, NULL, BCRYPT_KEY_DATA_BLOB, NULL, NULL,
            &export_size, 0);
        if (status)
            throw runtime_error("BCryptExportKey: measuring export size");

        PUCHAR _delivery_key = new UCHAR[export_size];
        ULONG copied;
        status = BCryptExportKey(hDeliveryKey, NULL, BCRYPT_KEY_DATA_BLOB, _delivery_key, export_size,
            &copied, 0);
        if (status) {
            delete[] _delivery_key;
            throw runtime_error("BCryptExportKey: delivery_key");
        }

        BCRYPT_OAEP_PADDING_INFO pi;
        memset(&pi, 0, sizeof(BCRYPT_OAEP_PADDING_INFO));
        pi.pszAlgId = BCRYPT_SHA256_ALGORITHM;

        ULONG result_size = 0;
        PUCHAR _result = NULL;
        ULONG blob_size = export_size - sizeof(BCRYPT_KEY_DATA_BLOB_HEADER);
        PUCHAR blob = _delivery_key + sizeof(BCRYPT_KEY_DATA_BLOB_HEADER);
        status = BCryptEncrypt(hUpdateKey, blob, blob_size, &pi, NULL, 0, NULL, 0, &result_size, BCRYPT_PAD_OAEP);
        if (status) {
            delete[] _delivery_key;
            BCryptDestroyKey(hUpdateKey);
            throw runtime_error("BCryptEncrypt: calculating result size");
        }

        _result = new UCHAR[result_size + 1];
        status = BCryptEncrypt(hUpdateKey, blob, blob_size, &pi, NULL, 0, _result, result_size, &copied, BCRYPT_PAD_OAEP);
        delete[] _delivery_key;
        if (status) {
            BCryptDestroyKey(hUpdateKey);
            delete[] _result;
            throw runtime_error("BCryptEncrypt: encrypting using update_key");
        }

        BCryptDestroyKey(hUpdateKey);

        stringstream s;
        for (ULONG i = 0; i < copied; i++) {
            s << hex << setw(2) << setfill('0');
            s << (int)_result[i];
        }
        delete[] _result;
        s >> result;

        return result;
    }

    void GateKeeper::enable_update()
    {
        LONG lResult = RegOpenKeyEx(cu, updater_reg_path, 0, KEY_WRITE, &hkUpdater);
        if (lResult != ERROR_SUCCESS)
            return;

        lResult = RegSetValueExW(hkUpdater, NULL, 0, REG_SZ, (const BYTE *) _T("1"), sizeof(TCHAR)*2);
    }

    void GateKeeper::disable_update()
    {
        LONG lResult = RegOpenKeyEx(cu, updater_reg_path, 0, KEY_WRITE, &hkUpdater);
        if (lResult != ERROR_SUCCESS)
            return;

        lResult = RegSetValueEx(hkUpdater, NULL, 0, REG_SZ, (const BYTE *) _T("0"), sizeof(TCHAR) * 2);
    }

    bool GateKeeper::update_enabled()
    {
        bool enabled = true;

        DWORD esize;
        RegGetValue(cu, updater_reg_path, NULL, RRF_RT_REG_SZ, NULL, NULL, &esize);
        if (esize) {
            TCHAR* edata = new TCHAR[esize];
            RegGetValue(cu, updater_reg_path, NULL, RRF_RT_REG_SZ, NULL, edata, &esize);
            if (tstring(edata) == _T("0"))
                enabled = false;
            delete[] edata;
        }

        return enabled;
    }

    GateKeeper::product_list GateKeeper::registered_products()
    {
        product_list products;

        // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724872(v=vs.85).aspx
        static TCHAR value_name[16384];
        DWORD value_name_size;
        static TCHAR value[L_MAX_URL_LENGTH + 1];
        DWORD value_size;

        LONG lResult = ERROR_SUCCESS;
        for (DWORD i = 0; lResult == ERROR_SUCCESS; i++) {
            value_name_size = 16383;
            value_size = L_MAX_URL_LENGTH + 1;
            lResult = RegEnumValue(hkUpdater, i, value_name, &value_name_size, NULL, NULL, (LPBYTE)value, &value_size);
            if (lResult == ERROR_SUCCESS) {
                products.push_back({ value_name, value });
            }
        }

        return products;
    }

    void GateKeeper::execute_file(tstring filename)
    {
        HANDLE hMutex = CreateMutex(NULL, TRUE, _T("PEPINSTALLERMUTEX"));
        if (hMutex) {
            CloseHandle(hMutex);
            ShellExecute(NULL, _T("open"), filename.c_str(), NULL, NULL, SW_SHOW);
        }
    }

    tstring GateKeeper::get_lockFile()
    {
        static const tstring _fileName = _T("\\pEpSetup.lck");
        static tstring fileName;

        if (fileName.length() == 0) {
            unique_ptr < TCHAR[] > _pathName(new TCHAR[MAX_PATH + 1]);
            DWORD size = GetTempPath(MAX_PATH, _pathName.get());
            if (size > MAX_PATH - _fileName.size())
                throw runtime_error("TEMP path too long");

            fileName = _pathName.get();
            fileName += _fileName;
        }

        return fileName;
    }

    // Retrieving Headers Using HTTP_QUERY_CUSTOM
    static tstring httpQueryCustom(HINTERNET hHttp, tstring header)
    {
        DWORD dwResult = 0;
        LPTSTR lpOutBuffer = StrDup(header.c_str());

    retry:

        if (!HttpQueryInfo(hHttp, HTTP_QUERY_CUSTOM, (LPVOID)lpOutBuffer, &dwResult, NULL))
        {
            if (GetLastError() == ERROR_HTTP_HEADER_NOT_FOUND)
            {
                // Code to handle the case where the header isn't available.
                LocalFree(lpOutBuffer);
                throw(runtime_error("ERROR_HTTP_HEADER_NOT_FOUND"));
            }
            else
            {
                // Check for an insufficient buffer.
                if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                {
                    // Allocate the necessary buffer.
                    LocalFree(lpOutBuffer);
                    lpOutBuffer = (LPTSTR)LocalAlloc(LMEM_FIXED, dwResult + 1);

                    // Rewrite the header name in the buffer.
                    StringCchPrintf(lpOutBuffer, dwResult, header.c_str());

                    // Retry the call.
                    goto retry;
                }
                else
                {
                    // Error handling code.
                    LocalFree(lpOutBuffer);
                    // FIXME: Add GetLastError()
                    throw(runtime_error("Unknown"));
                }
            }
        }

        tstring result(lpOutBuffer);
        LocalFree(lpOutBuffer);

        return result;
    }

    bool GateKeeper::update_product(product p, DWORD context)
    {
        {
            HANDLE file = CreateFile(get_lockFile().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file == INVALID_HANDLE_VALUE) {
                return false;
            }
            else {
                CloseHandle(file);
                DeleteFile(get_lockFile().c_str());
            }
        }

        BCRYPT_KEY_HANDLE dk = delivery_key();
#ifdef UNICODE
        tstring delivery = utility::utf16_string(wrapped_delivery_key(dk));
#else
        tstring delivery = wrapped_delivery_key(delivery_key());
#endif
        tstring url = p.second;
        url += _T("&challenge=");
        url += delivery;
        tstring headers;
        HINTERNET hUrl = InternetOpenUrl(internet, url.c_str(), headers.c_str(), headers.length(),
            INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE, context);
        if (hUrl == NULL)
            return false;

        string crypted;
        string unencrypted;
        UCHAR iv[12];
        UCHAR nonce[sizeof(iv)];
        UCHAR tag[16];
        tstring filename;
        HANDLE hFile = NULL;
        char *unencrypted_buffer = NULL;
        bool result = false;

        try {

            DWORD reading;
            InternetReadFile(hUrl, iv, sizeof(iv), &reading);

            if (reading)
                mainWindow.ShowNotificationInfo(r(IDS_DOWNLOADTITLE), r(IDS_DOWNLOADTEXT));

            if (reading) do {
                static char buffer[1024 * 1024];
                BOOL bResult = InternetReadFile(hUrl, buffer, 1024 * 1024, &reading);
                if (!bResult || !reading)
                    break;
                crypted += string(buffer, reading);
            } while (1);

            tstring contentDisposition = httpQueryCustom(hUrl, _T("Content-Disposition"));

            tregex filenameRegex(_T("filename=.([^\"]*)"), regex::extended); //FIXME: case insensitive
            tsmatch match;

            if (regex_search(contentDisposition, match, filenameRegex)) {
                filename = match[1];
            }

            InternetCloseHandle(hUrl);
            hUrl = NULL;

            memcpy(nonce, iv, sizeof(iv));

            BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO authInfo;
            BCRYPT_INIT_AUTH_MODE_INFO(authInfo);
            authInfo.pbNonce = nonce;
            authInfo.cbNonce = sizeof(nonce);
            authInfo.pbTag = tag;
            authInfo.cbTag = sizeof(tag);

            ULONG unencrypted_size;
            NTSTATUS status = BCryptDecrypt(dk, (PUCHAR)crypted.data(), crypted.size(),
                &authInfo, iv, sizeof(iv), NULL, 0, &unencrypted_size, 0);
            if (status)
                goto closing;

            unencrypted_buffer = new char[unencrypted_size];

            PUCHAR crypted_data = (PUCHAR)crypted.data();
            ULONG crypted_size = (ULONG)crypted.size() - sizeof(tag);
            memcpy(tag, crypted_data + crypted_size, sizeof(tag));

            status = BCryptDecrypt(dk, crypted_data, crypted_size,
                &authInfo, iv, sizeof(iv), (PUCHAR)unencrypted_buffer, unencrypted_size, &unencrypted_size, 0);
            if (status)
                goto closing;

            BCryptDestroyKey(dk);

            TCHAR download_path[MAX_PATH + 1];
            PWSTR _downloads;
            SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &_downloads);
            StringCchCopy(download_path, MAX_PATH, _downloads);
            CoTaskMemFree(_downloads);

            GetTempPath(MAX_PATH, download_path);

            if (filename == _T("")) {
                filename = download_path;
                filename += _T("\\pEp_");
                filename += delivery.substr(0, 32);
                filename += _T(".msi");
            }
            else {
                filename = tstring(download_path) + _T("\\") + filename;
            }

            hFile = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (!hFile)
                goto closing;
            DWORD writing;
            WriteFile(hFile, unencrypted_buffer, unencrypted_size, &writing, NULL);
            CloseHandle(hFile);
            hFile = NULL;
            delete[] unencrypted_buffer;
            unencrypted_buffer = nullptr;
        }
        catch (exception&) {
            goto closing;
        }

        execute_file(filename);
        result = true;

    closing:
        if (unencrypted_buffer)
            delete[] unencrypted_buffer;
        if (hFile)
            CloseHandle(hFile);
        if (hUrl)
            InternetCloseHandle(hUrl);
        BCryptDestroyKey(dk);

        return result;
    }

    bool GateKeeper::is_product_url_exists(product p, DWORD context) {
        {
            HANDLE file = CreateFile(get_lockFile().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file == INVALID_HANDLE_VALUE) {
                return false;
            }
            else {
                CloseHandle(file);
                DeleteFile(get_lockFile().c_str());
            }
        }

        BCRYPT_KEY_HANDLE dk = delivery_key();
#ifdef UNICODE
        tstring delivery = utility::utf16_string(wrapped_delivery_key(dk));
#else
        tstring delivery = wrapped_delivery_key(delivery_key());
#endif
        tstring url = p.second;
        url += _T("&challenge=");
        url += delivery;
        tstring headers;
        HINTERNET hUrl = InternetOpenUrl(internet, url.c_str(), headers.c_str(), headers.length(),
            INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_UI | INTERNET_FLAG_SECURE, context);
        if (hUrl == NULL)
            return false;
        return true;
    }
    bool GateKeeper::Is_update_available() {
        bool result = true;
        product_list products = registered_products();
        DWORD context = 0;
        for (auto i = products.begin(); i != products.end(); i++) {
            try {
                result = result && is_product_url_exists(*i, context++);
            }
            catch (exception&) {
                result = false;
            }
        }
        return result;
    }

    void GateKeeper::update_now()
    {
        NTSTATUS status = BCryptOpenAlgorithmProvider(&hAES, BCRYPT_AES_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;
        status = BCryptSetProperty(hAES, BCRYPT_CHAINING_MODE, (PUCHAR)BCRYPT_CHAIN_MODE_GCM, sizeof(BCRYPT_CHAIN_MODE_GCM), 0);
        if (status)
            goto closing;

        status = BCryptOpenAlgorithmProvider(&hRSA, BCRYPT_RSA_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;

        internet = InternetOpen(_T("pEp"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
        if (!internet)
            goto closing;

        {
            product_list products = registered_products();
            DWORD context = 0;

            for (auto i = products.begin(); i != products.end(); i++) {
                try {
                    update_product(*i, context++);
                }
                catch (exception&) {

                }
            }
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

    void GateKeeper::show_notification(tstring title, tstring text) 
    {
        mainWindow.ShowNotificationInfo(title, text);
    }

    GateKeeper *GateKeeper::the_gatekeeper = nullptr;

} // namespace pEp
