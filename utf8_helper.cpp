#include "stdafx.h"
#include "utf8_helper.h"

using namespace std;

string utf8_string(wstring wstr, NORM_FORM norm) {
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

string utf8_string(BSTR bstr, NORM_FORM norm) {
	return utf8_string((wstring)(wchar_t *)_bstr_t(bstr, true), norm);
}

wstring utf16_string(string str) {
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

_bstr_t utf16_bstr(string str) {
	return _bstr_t(utf16_string(str).c_str());
}
