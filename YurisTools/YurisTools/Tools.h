#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>


class Tools
{
public:
	static unsigned int GetFileSize(std::ifstream& fsFile);
	static std::wstring StrToWStr(std::string& strString, UINT uCodePage);
};