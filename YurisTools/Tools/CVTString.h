#pragma once
#include <string>

class CVTString
{
public:
	static std::locale& GetCVT();
	static void StrToWStr(std::string& strString, std::wstring& wsString, unsigned int uCodePage);
	static void WStrToStr(std::wstring& wsString, std::string& strString, unsigned int uCodePage);
	static void StrToWStr_CVT(std::string& strString, std::wstring& wsString, unsigned int uCodePage);
	static void WStrToStr_CVT(std::wstring& wsString, std::string& strString, unsigned int uCodePage);

};