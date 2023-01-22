#include "MemX.h"


namespace TDA
{
	BOOL MemX::WriteMemory(LPVOID lpAddress, LPCVOID lpBuffer, SIZE_T szSize)
	{
		DWORD oldProtect = 0;
		BOOL isWrite = FALSE;
		BOOL isProtect = FALSE;


		isProtect = VirtualProtectEx(GetCurrentProcess(), lpAddress, szSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		isWrite = WriteProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, szSize, NULL);
		if (isProtect && isWrite)
		{
			return TRUE;
		}
		else
		{
			MessageBoxW(NULL, L"WriteMemory Failed!!", NULL, NULL);
			return FALSE;
		}
	}

	BOOL MemX::ReadMemory(LPVOID lpAddress, LPVOID lpBuffer, SIZE_T szSize)
	{
		DWORD oldProtect = 0;
		BOOL isRead = FALSE;
		BOOL isProtect = FALSE;


		isProtect = VirtualProtectEx(GetCurrentProcess(), lpAddress, szSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		isRead = ReadProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, szSize, NULL);
		if (isProtect && isRead)
		{
			return TRUE;
		}
		else
		{
			MessageBoxW(NULL, L"ReadMemory Failed!!", NULL, MB_OK);
			return FALSE;
		}
	}

	DWORD MemX::MemSearch(DWORD dwBeginAddr, PBYTE aSearchCode, SIZE_T szCode, BOOL isBackward)
	{
		for (; ; )
		{
			if (dwBeginAddr < 0x7FFF0000 && dwBeginAddr > 0x00010000)
			{
				//DWORD oldProtect = 0;
				//VirtualProtect((LPVOID)beginAddr, lenOfCode, PAGE_EXECUTE_READWRITE, &oldProtect);
				if (!memcmp(aSearchCode, (void*)dwBeginAddr, szCode))
				{
					return dwBeginAddr;
				}

				if (isBackward)
				{
					dwBeginAddr++;
				}
				else
				{
					dwBeginAddr--;
				}
			}
			else
			{
				return 0;
			}
		}
	}

	BOOL MemX::SetHook(DWORD dwRawAddr, DWORD dwTarAddr, SIZE_T szRawSize)
	{
		BOOL isProtect = 0;
		DWORD oldProtect = 0;
		PBYTE allocateAddr = 0;
		DWORD relativeAddr = 0;
		BYTE rawJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
		BYTE retJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
		BYTE tarCal[] = { 0xE8,0x00,0x00,0x00,0x00 };

		isProtect = VirtualProtect((LPVOID)dwRawAddr, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);
		allocateAddr = (PBYTE)VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (allocateAddr && isProtect)
		{
			//Copy the Code for the original address to alloc address
			memcpy(allocateAddr, (PVOID)dwRawAddr, szRawSize);

			//Write Jmp Code
			relativeAddr = (DWORD)allocateAddr - dwRawAddr - sizeof(rawJmp);
			memcpy(&rawJmp[1], &relativeAddr, sizeof(DWORD));
			memcpy((PBYTE)dwRawAddr, rawJmp, sizeof(rawJmp));

			//Write Call TarFunc Code
			relativeAddr = dwTarAddr - (DWORD)(&allocateAddr[szRawSize]) - sizeof(tarCal);
			memcpy(&tarCal[1], &relativeAddr, sizeof(DWORD));
			memcpy(&allocateAddr[szRawSize], tarCal, sizeof(tarCal));

			//Write Ret Code
			relativeAddr = (dwRawAddr + szRawSize) - (DWORD)(&allocateAddr[szRawSize + sizeof(tarCal)]) - sizeof(retJmp);
			memcpy(&retJmp[1], &relativeAddr, sizeof(DWORD));
			memcpy(&allocateAddr[szRawSize + sizeof(tarCal)], retJmp, sizeof(retJmp));

			return TRUE;
		}
		else
		{
			MessageBoxW(NULL, L"SetHook Failed!!", NULL, NULL);
			return FALSE;
		}
	}
}

