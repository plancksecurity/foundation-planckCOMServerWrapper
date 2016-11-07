#include "stdafx.h"

#include "GateKeeper.h"
#include "pEpCOMServerAdapter.h"
#include "utf8_helper.h"

using namespace std;

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

    pbPublicKey = (PBYTE) CoTaskMemAlloc(cbKey);
    if (pbPublicKey == NULL) {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }

    ZeroMemory(pbPublicKey, cbKey);
    pRsaBlob = (BCRYPT_RSAKEY_BLOB *) (pbPublicKey);

    //
    // Make the Public Key Blob Header
    //

    pRsaBlob->Magic = BCRYPT_RSAPUBLIC_MAGIC;
    pRsaBlob->BitLength = pKey->rsapubkey.bitlen;
    pRsaBlob->cbPublicExp = cbExp;
    pRsaBlob->cbModulus = cbModulus;
    pRsaBlob->cbPrime1 = 0;
    pRsaBlob->cbPrime2 = 0;

    pbCurrent = (PBYTE) (pRsaBlob + 1);

    //
    // Copy pubExp Big Endian 
    //

    ReverseMemCopy(pbCurrent, (PBYTE) &dwExp, cbExp);
    pbCurrent += cbExp;

    //
    // Copy Modulus Big Endian 
    //

    ReverseMemCopy(pbCurrent, pKey->modulus, cbModulus);

    //
    // Import the public key
    //

    hr = BCryptImportKeyPair(hAlg, NULL, BCRYPT_RSAPUBLIC_BLOB, phKey, (PUCHAR) pbPublicKey, cbKey, 0);

cleanup:
    CoTaskMemFree(pbPublicKey);
    return hr;
}

namespace pEp {

    const LPCTSTR GateKeeper::plugin_reg_path = _T("Software\\Microsoft\\Office\\Outlook\\Addins\\pEp");
    const LPCTSTR GateKeeper::plugin_reg_value_name = _T("LoadBehavior");
    const LPCTSTR GateKeeper::updater_reg_path = _T("Software\\pEp\\Updater");

    const time_t GateKeeper::cycle = 7200;   // 7200 sec is 2 h
    const time_t GateKeeper::fraction = 10;  // first update is at 10% of cycle
    const DWORD GateKeeper::waiting = 10000; // 10000 ms is 10 sec

    GateKeeper::GateKeeper(CpEpCOMServerAdapterModule * self)
        : _self(self), now(time(NULL)), next(now + time_diff()), hkUpdater(NULL), hkPluginStart(NULL),
            internet(NULL), hAES(NULL), hRSA(NULL)
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

            lResult = RegOpenKeyEx(cu, plugin_reg_path, 0, KEY_WRITE, &hkPluginStart);
            assert(lResult == ERROR_SUCCESS);
            if (lResult != ERROR_SUCCESS)
                return;
            RegCloseKey(hkPluginStart);
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

            uniform_int_distribution<time_t> dist(0, cycle/fraction);

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
        if (!hkPluginStart)
            return;

        LONG lResult = RegOpenKeyEx(cu, plugin_reg_path, 0, KEY_WRITE, &hkPluginStart);
        assert(lResult == ERROR_SUCCESS);
        if (lResult != ERROR_SUCCESS)
            return;

        DWORD v = 3;
        lResult = RegSetValueEx(hkPluginStart, plugin_reg_value_name, 0, REG_DWORD, (const BYTE *) &v, sizeof(DWORD));
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
            key.dw_key[i] = (uint32_t) dist(gen);

        BCRYPT_KEY_HANDLE hKey;

        NTSTATUS status = BCryptGenerateSymmetricKey(hAES, &hKey, NULL, 0, (PUCHAR) &key, (ULONG) sizeof(aeskey_t), 0);
        assert(status == 0);
        if (status)
            throw runtime_error("BCryptGenerateSymmetricKey");

#ifndef NDEBUG
        DWORD keylength = 0;
        ULONG copied = 0;
        status = BCryptGetProperty(hKey, BCRYPT_KEY_LENGTH, (PUCHAR) &keylength, sizeof(DWORD), &copied, 0);
        assert(keylength == 256);
#endif

        return hKey;
    }

    string GateKeeper::wrapped_delivery_key(BCRYPT_KEY_HANDLE hDeliveryKey)
    {
        string result;

        BCRYPT_KEY_HANDLE hUpdateKey;
        string _update_key = update_key();

        PCERT_PUBLIC_KEY_INFO uk;
        DWORD uk_size;

        BOOL bResult = CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO,
                (const BYTE *) _update_key.data(), _update_key.size(), CRYPT_DECODE_ALLOC_FLAG, NULL, &uk, &uk_size);
        if (!bResult)
            throw runtime_error("CryptDecodeObjectEx: X509_PUBLIC_KEY_INFO");

        PUBLIC_KEY_VALUES *_uk;
        DWORD _uk_size;

        bResult = CryptDecodeObjectEx(X509_ASN_ENCODING, RSA_CSP_PUBLICKEYBLOB,
            uk->PublicKey.pbData, uk->PublicKey.cbData, CRYPT_DECODE_ALLOC_FLAG, NULL, &_uk, &_uk_size);
        LocalFree(uk);
        if (!bResult)
            throw runtime_error("CryptDecodeObjectEx: X509_PUBLIC_KEY_INFO");

        HRESULT hResult = ImportRsaPublicKey(hRSA, _uk, &hUpdateKey);
        LocalFree(_uk);
        if (hResult)
            throw runtime_error("ImportRsaPublicKey");

        ULONG psize;
        NTSTATUS status = BCryptGetProperty(hUpdateKey, BCRYPT_ALGORITHM_NAME, NULL, 0, &psize, 0);
        char *prop = new char[psize];
        TCHAR *_prop = (TCHAR *) prop;
        BCryptGetProperty(hUpdateKey, BCRYPT_ALGORITHM_NAME, (PUCHAR) prop, psize, &psize, 0);

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

        ULONG result_size;
        PUCHAR _result = NULL;
        ULONG blob_size = export_size - sizeof(BCRYPT_KEY_DATA_BLOB_HEADER);
        PUCHAR blob = _delivery_key + sizeof(BCRYPT_KEY_DATA_BLOB_HEADER);
        status = BCryptEncrypt(hUpdateKey, blob, blob_size, &pi, NULL, 0, NULL, 0, &result_size, BCRYPT_PAD_OAEP);
        if (status) {
            delete[] _delivery_key;
            BCryptDestroyKey(hUpdateKey);
            throw runtime_error("BCryptEncrypt: calculating result size");
        }

        _result = new UCHAR[result_size];
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
            s << (int) _result[i];
        }
        delete[] _result;
        s >> result;

        return result;
    }

    GateKeeper::product_list& GateKeeper::registered_products()
    {
        static product_list products;

        // https://msdn.microsoft.com/en-us/library/windows/desktop/ms724872(v=vs.85).aspx
        TCHAR value_name[16384];
        DWORD value_name_size;
        TCHAR value[L_MAX_URL_LENGTH + 1];
        DWORD value_size;

        products.empty();

        LONG lResult = ERROR_SUCCESS;
        for (DWORD i = 0; lResult == ERROR_SUCCESS; i++) {
            value_name_size = 16383;
            value_size = L_MAX_URL_LENGTH + 1;
            lResult = RegEnumValue(hkUpdater, i, value_name, &value_name_size, NULL, NULL, (LPBYTE) value, &value_size);
            if (lResult == ERROR_SUCCESS) {
                products.push_back({ value_name, value });
            }
        }

        return products;
    }

    void GateKeeper::install_msi(tstring filename)
    {
		HANDLE hMutex = CreateMutex(NULL, TRUE, _T("PEPINSTALLERMUTEX"));
		if (hMutex) {
			CloseHandle(hMutex);
			ShellExecute(NULL, _T("open"), filename.c_str(), NULL, NULL, SW_SHOW);
		}
    }

    void GateKeeper::update_product(product p, DWORD context)
    {
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
            return;

        string crypted;
        string unencrypted;
        UCHAR iv[12];
        UCHAR nonce[sizeof(iv)];
        UCHAR tag[16];
        tstring filename;
        HANDLE hFile = NULL;
        char *unencrypted_buffer = NULL;

        try {
            DWORD reading;
            InternetReadFile(hUrl, iv, sizeof(iv), &reading);

            if (reading) do {
                static char buffer[1024*1024];
                BOOL bResult = InternetReadFile(hUrl, buffer, 1024*1024, &reading);
                if (!bResult || !reading)
                    break;
                crypted += string(buffer, reading);
            } while (1);
        }
        catch (exception&) {
            goto closing;
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
        NTSTATUS status = BCryptDecrypt(dk, (PUCHAR) crypted.data(), crypted.size(),
                &authInfo, iv, sizeof(iv), NULL, 0, &unencrypted_size, 0);
        if (status)
            goto closing;
        
        unencrypted_buffer = new char[unencrypted_size];
        PUCHAR crypted_data = (PUCHAR) crypted.data();
        ULONG crypted_size = (ULONG) crypted.size() - sizeof(tag);
        memcpy(tag, crypted_data + crypted_size, sizeof(tag));

        status = BCryptDecrypt(dk, crypted_data, crypted_size,
            &authInfo, iv, sizeof(iv), (PUCHAR) unencrypted_buffer, unencrypted_size, &unencrypted_size, 0);
        if (status)
            goto closing;

        BCryptDestroyKey(dk);

        TCHAR temp_path[MAX_PATH + 1];
        GetTempPath(MAX_PATH, temp_path);
        filename = temp_path;
        filename += _T("\\pEp_");
        filename += delivery.substr(0, 32);
        filename += _T(".msi");

        hFile = CreateFile(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (!hFile)
            goto closing;
        DWORD writing;
        WriteFile(hFile, unencrypted_buffer, unencrypted_size, &writing, NULL);
        CloseHandle(hFile);

        install_msi(filename);

        return;

    closing:
        if (unencrypted_buffer)
            delete[] unencrypted_buffer;
        if (hFile)
            CloseHandle(hFile);
        if (hUrl)
            InternetCloseHandle(hUrl);
        BCryptDestroyKey(dk);
    }

    void GateKeeper::keep_updated()
    {
        NTSTATUS status = BCryptOpenAlgorithmProvider(&hAES, BCRYPT_AES_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;
        status = BCryptSetProperty(hAES, BCRYPT_CHAINING_MODE, (PUCHAR) BCRYPT_CHAIN_MODE_GCM, sizeof(BCRYPT_CHAIN_MODE_GCM), 0);
        if (status)
            goto closing;

        status = BCryptOpenAlgorithmProvider(&hRSA, BCRYPT_RSA_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
        assert(status == 0);
        if (status)
            goto closing;

        internet = InternetOpen(_T("pEp"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
        if (!internet)
            goto closing;

        product_list& products = registered_products();
        DWORD context = 0;

        for (auto i = products.begin(); i != products.end(); i++) {
            try {
                update_product(*i, context++);
            }
            catch (exception&) {
            
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

} // namespace pEp
