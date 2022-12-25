#pragma once
#include <Windows.h>
#include <iostream>

class Console
{
public:
	static FILE* SetConsole(LPCWSTR lpTitle);
};