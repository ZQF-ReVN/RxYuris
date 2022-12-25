#include "CVTString.h"
#include <Windows.h>
#include <codecvt>

void CVTString::StrToWStr(std::string& strString, std::wstring& wsString, unsigned int uCodePage)
{
	int len = 0;
	wchar_t* buffer = nullptr;

	len = MultiByteToWideChar(uCodePage, NULL, strString.c_str(), static_cast<int>(strString.size()), NULL, NULL);
	buffer = new wchar_t[len + 1];
	MultiByteToWideChar(uCodePage, NULL, strString.c_str(), static_cast<int>(strString.size()), buffer, len);
	buffer[len] = L'\0';
	wsString.append(buffer);

	delete[] buffer;
}

void CVTString::WStrToStr(std::wstring& wsString, std::string& strString, unsigned int uCodePage)
{
	int len = 0;
	char* buffer = nullptr;

	len = WideCharToMultiByte(uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), NULL, NULL, NULL, NULL);
	buffer = new char[len + 1];
	WideCharToMultiByte(uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	strString.append(buffer);

	delete[] buffer;
}

//Essentially it is still call MultiByteToWideChar / WideCharToMultiByte
void CVTString::StrToWStr_CVT(std::string& strString, std::wstring& wsString, unsigned int uCodePage)
{
	std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString(new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage)));
	wsString = cvtString.from_bytes(strString);
}

void CVTString::WStrToStr_CVT(std::wstring& wsString, std::string& strString, unsigned int uCodePage)
{
	std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString(new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage)));
	strString = cvtString.to_bytes(wsString);
}