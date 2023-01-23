#include <iostream>

#include "..\YurisStaticLibrary\YPF.h"

using namespace YurisStaticLibrary;


int wmain(int argc, wchar_t* argv[])
{
	std::wstring fileName;
	std::wcout << L"input file name:";
	std::wcin >> fileName;

	YPF ypf(fileName);
	ypf.DecodeFile_WZ();
}