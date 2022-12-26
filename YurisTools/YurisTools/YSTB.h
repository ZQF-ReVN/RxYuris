#pragma once
#include <iostream>

class YSTB
{
public:
	static void TextDump_V2(std::string strYSTB);
	static void XorScript(std::string strYSTB, unsigned char* aXorKey);
	static void GuessXorKey(std::string strYSTB, unsigned char* aXorKey);

private:

};