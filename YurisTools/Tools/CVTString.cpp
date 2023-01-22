#include "CVTString.h"
#include <Windows.h>
#include <codecvt>

std::locale& CVTString::GetCVT_UTF8()
{
	static std::locale cvtUTF8 = std::locale
	(
		std::locale::empty(),
		new std::codecvt_utf8
		<
		wchar_t,
		0x10ffff,
		std::codecvt_mode(std::consume_header | std::generate_header | std::little_endian)
		>
	);

	return cvtUTF8;
}

void CVTString::StrToWStr(std::string& strString, std::wstring& wsString, unsigned int uCodePage)
{
	int charCount = MultiByteToWideChar
	(
		uCodePage, NULL, strString.c_str(), static_cast<int>(strString.size()), NULL, NULL
	);

	if (charCount == 0) return;

	wsString.resize(charCount);

	MultiByteToWideChar
	(
		uCodePage, NULL, strString.c_str(), static_cast<int>(strString.size()), const_cast<wchar_t*>(wsString.data()), charCount
	);
}

void CVTString::WStrToStr(std::wstring& wsString, std::string& strString, unsigned int uCodePage)
{
	int wcharCount = WideCharToMultiByte
	(
		uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), NULL, NULL, NULL, NULL
	);

	if (wcharCount == 0) return;

	strString.resize(wcharCount);

	WideCharToMultiByte
	(
		uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), const_cast<char*>(strString.data()), wcharCount, NULL, NULL
	);
}

//Essentially it is still call MultiByteToWideChar / WideCharToMultiByte
void CVTString::StrToWStr_CVT(std::string& strString, std::wstring& wsString, unsigned int uCodePage)
{
	std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString
	(
		new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage))
	);
	wsString = cvtString.from_bytes(strString);
}

void CVTString::WStrToStr_CVT(std::wstring& wsString, std::string& strString, unsigned int uCodePage)
{
	std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString
	(
		new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage))
	);
	strString = cvtString.to_bytes(wsString);
}