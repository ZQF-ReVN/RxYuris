#pragma once
#include <Windows.h>
#include <iostream>


namespace TDA
{
	class Console
	{
	public:
		static FILE* SetConsole(LPCWSTR lpTitle);
	};
}

