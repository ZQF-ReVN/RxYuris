#pragma once
#include <iostream>

class YSTB
{
public:
	static void XorScript(std::string strYSTB, unsigned char* aXorKey);
	static void GuessXorKey(std::string strYSTB, unsigned char* aXorKey);

private:

};