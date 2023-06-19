#include "Mem.h"


namespace Rut
{
	namespace MemX
	{
		BOOL WriteMemory(LPVOID lpAddress, LPCVOID lpBuffer, SIZE_T nSize)
		{
			DWORD old = 0;
			BOOL protect = VirtualProtectEx(GetCurrentProcess(), lpAddress, nSize, PAGE_EXECUTE_READWRITE, &old);
			BOOL written = WriteProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, nSize, NULL);

			if (protect && written) return TRUE;

			MessageBoxW(NULL, L"WriteMemory Failed!!", NULL, NULL);

			return FALSE;
		}

		BOOL ReadMemory(LPVOID lpAddress, LPVOID lpBuffer, SIZE_T nSize)
		{
			DWORD old = 0;
			BOOL protect = VirtualProtectEx(GetCurrentProcess(), lpAddress, nSize, PAGE_EXECUTE_READWRITE, &old);
			BOOL written = ReadProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, nSize, NULL);

			if (protect && written) return TRUE;

			MessageBoxW(NULL, L"ReadMemory Failed!!", NULL, NULL);

			return FALSE;
		}

		DWORD MemSearch(DWORD pFind, SIZE_T szFind, PBYTE pToFind, SIZE_T szToFind, BOOL backward)
		{
			if ((pFind >= 0x7FFF0000) || (pFind <= 0x00010000) || !szToFind) return NULL;

			if (!backward)
			{
				for (size_t ite = 0; ite < szFind; ite++)
				{
					if (!memcmp(pToFind, (void*)pFind++, szToFind)) return (pFind - 1);
				}
			}
			else
			{
				for (size_t ite = 0; ite < szFind; ite++)
				{
					if (!memcmp(pToFind, (void*)pFind--, szToFind)) return (pFind + 1);
				}
			}

			MessageBoxW(NULL, L"MemSearch Failed!!", NULL, NULL);
			ExitProcess(0);
			return NULL;
		}
	}
}