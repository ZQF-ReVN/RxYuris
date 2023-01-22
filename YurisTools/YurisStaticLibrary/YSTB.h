#pragma once
#include <string>

class YSTB
{
public:
	static bool TextInset_V2(std::string strYSTB, unsigned int uiCodePage);
	static bool TextDump_V2(std::string strYSTB, unsigned int uiCodePage);
	static bool XorScript(std::string strYSTB, unsigned char* aXorKey);
	static void GuessXorKey(std::string strYSTB, unsigned char* aXorKey);

private:

};