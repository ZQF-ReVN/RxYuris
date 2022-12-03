#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

class Tools
{
public:
	static unsigned int GetFileSize(std::ifstream& fsFile);
	static std::wstring StrToWStr(std::string& strString, UINT uCodePage);
};