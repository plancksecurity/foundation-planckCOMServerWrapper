#include "stdafx.h"
#include "utf8_helper.h"

using namespace ATL;
using namespace std;

namespace pEp {
    namespace utility {

        string utf8_string(wstring wstr, NORM_FORM norm)
        {
            if (wstr.size() == 0)
                return string();

            wstring _wstr_normalized;

            if (norm == NormalizationOther)
                _wstr_normalized = wstr;
            else {
                int size = NormalizeString(norm, wstr.c_str(), -1, NULL, 0);
                assert(size > 0);
                if (size > 0) {
                    wchar_t *buf = new wchar_t[size];
                    NormalizeString(norm, wstr.c_str(), -1, buf, size);
                    _wstr_normalized = buf;
                    delete[] buf;
                }
                else
                    throw out_of_range("input wstring is not valid while normalizing.");
            }
            string result;

            int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, _wstr_normalized.c_str(), -1, NULL, 0, NULL, NULL);
            assert(size);
            if (size) {
                char *buf = new char[size];
                WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, _wstr_normalized.c_str(), -1, buf, size, NULL, NULL);
                result = buf;
                delete[] buf;
            }
            else
                throw out_of_range("input wstring is not valid while converting UTF-16 to UTF-8.");

            return result;
        }

        string utf8_string(BSTR bstr, NORM_FORM norm)
        {
            if (bstr == NULL)
                return "";

            return utf8_string((wstring) (wchar_t *) _bstr_t(bstr, true), norm);
        }

        wstring utf16_string(string str)
        {
            if (str.size() == 0)
                return wstring();

            wstring result;

            int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), -1, NULL, 0);
            assert(size);
            if (size) {
                wchar_t * buf = new wchar_t[size];
                MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), -1, buf, size);
                result = buf;
                delete[] buf;
            }
            else
                throw out_of_range("input string is not valid while converting UTF-8 to UTF-16.");

            return result;
        }

        _bstr_t utf16_bstr(string str)
        {
            return _bstr_t(utf16_string(str).c_str());
        }

        CComSafeArray<BSTR> string_array(const ::stringlist_t *stringlist)
        {
            if (stringlist == NULL)
                return CComSafeArray<BSTR>((ULONG)0);

            CComSafeArray<BSTR> sa_string_list;
            int n = 0;
            for (const ::stringlist_t *k = stringlist; k != NULL; k = k->next) {
                if (k->value) {
                    HRESULT _result = sa_string_list.Add(utf16_bstr(k->value).Detach(), false);
                    assert(_result == S_OK);
                    if (_result == E_OUTOFMEMORY)
                        throw std::bad_alloc();
                    ++n;
                }
            }

            return sa_string_list;
        }

        ::stringlist_t * new_stringlist(const SAFEARRAY * safearray)
        {
            if (safearray == NULL)
                return NULL;

            CComSafeArray<BSTR> sa(safearray);
            int n_strings = 0;
            ::stringlist_t *_stringlist = ::new_stringlist((const char *) NULL);
            assert(_stringlist);
            if (_stringlist == NULL)
                throw std::bad_alloc();

            n_strings = sa.GetUpperBound() - sa.GetLowerBound() + 1;
            ::stringlist_t *k = _stringlist;
            for (int i = 0, j = sa.GetLowerBound(); i < n_strings; ++i, ++j) {
                k = ::stringlist_add(k, utf8_string(sa.GetAt(j)).c_str());
                assert(k);
                if (k == NULL) {
                    ::free_stringlist(_stringlist);
                    throw std::bad_alloc();
                }
            }

            return _stringlist;
        }

    }
}
