#pragma once
#include <corecrt_wstdio.h>

//Ria's Utility Library X
namespace Rut
{
	namespace ConsoleX
	{
		FILE* SetConsole(const wchar_t* lpTitle);
		bool PutConsoleA(const char* lpFormat, ...);
		bool PutConsoleW(const wchar_t* lpFormat, ...);
	}
}
