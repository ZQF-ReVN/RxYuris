#pragma once
#include <Windows.h>

class MemX
{
public:
	static BOOL WriteMemory(LPVOID lpAddress, LPCVOID lpBuffer, SIZE_T szSize);
	static BOOL ReadMemory(LPVOID lpAddress, LPVOID lpBuffer, SIZE_T szSize);
	static DWORD MemSearch(DWORD dwBeginAddr, PBYTE aSearchCode, SIZE_T szCode, BOOL isDirection);
	static BOOL SetHook(DWORD dwRawAddr, DWORD dwTarAddr, SIZE_T szRawSize);

};
