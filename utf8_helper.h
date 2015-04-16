#pragma once

std::string utf8_string(std::wstring wstr, NORM_FORM norm = NormalizationC);
std::string utf8_string(BSTR bstr, NORM_FORM norm = NormalizationC);
std::wstring utf16_string(std::string str);
_bstr_t utf16_bstr(std::string str);
