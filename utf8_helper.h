#pragma once

namespace pEp {
    namespace utility {

        std::string utf8_string(std::wstring wstr, NORM_FORM norm = NormalizationC);
        std::string utf8_string(BSTR bstr, NORM_FORM norm = NormalizationC);
        std::wstring utf16_string(std::string str);
        BSTR utf16_bstr(std::string str);
        LPSAFEARRAY string_array(const ::stringlist_t *stringlist);
        ::stringlist_t * new_stringlist(const SAFEARRAY * safearray);
    }
}
