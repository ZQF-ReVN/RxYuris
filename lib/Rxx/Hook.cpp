#include "Hook.h"
#include "Mem.h"

#include <Windows.h>

#include "../../third/detours/include/detours.h"
#pragma comment(lib,"../../third/detours/lib.X86/detours.lib")


namespace Rut
{
	namespace HookX
	{
		bool WriteHookCode(uint32_t uiRawAddress, uint32_t uiNewAddress, uint32_t szHookCode)
		{
			UCHAR code[0xF];
			memset(code, 0x90, 0xF);

			*(UCHAR*)(code + 0) = 0xE9;
			*(DWORD*)(code + 1) = uiNewAddress - uiRawAddress - 5;

			if (MemX::WriteMemory((LPVOID)uiRawAddress, &code, szHookCode)) return TRUE;

			MessageBoxW(NULL, L"WriteHookCode Failed!!", NULL, NULL);

			return FALSE;
		}

		bool WriteHookCode_RET(uint32_t uiRawAddress, uint32_t uiRetAddress, uint32_t uiNewAddress)
		{
			UCHAR code[0xF];
			memset(code, 0x90, 0xF);

			*(UCHAR*)(code + 0) = 0xE9;
			*(DWORD*)(code + 1) = uiNewAddress - uiRawAddress - 5;

			if (MemX::WriteMemory((LPVOID)uiRawAddress, &code, uiRetAddress - uiRawAddress)) return TRUE;

			MessageBoxW(NULL, L"WriteHookCode Failed!!", NULL, NULL);

			return FALSE;
		}

		bool SetHook(uint32_t uiRawAddr, uint32_t uiTarAddr, uint32_t szRawSize)
		{
			DWORD old = 0;
			DWORD rva = 0;
			BYTE rawJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
			BYTE retJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
			BYTE tarCal[] = { 0xE8,0x00,0x00,0x00,0x00 };

			BOOL protect = VirtualProtect((LPVOID)uiRawAddr, 0x1000, PAGE_EXECUTE_READWRITE, &old);
			PBYTE alloc = (PBYTE)VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (alloc && protect)
			{
				//Copy the Code for the original address to alloc address
				memcpy(alloc, (PVOID)uiRawAddr, szRawSize);

				//Write Jmp Code
				rva = (DWORD)alloc - uiRawAddr - sizeof(rawJmp);
				memcpy(&rawJmp[1], &rva, sizeof(DWORD));
				memcpy((PBYTE)uiRawAddr, rawJmp, sizeof(rawJmp));

				//Write Call TarFunc Code
				rva = uiTarAddr - (DWORD)(&alloc[szRawSize]) - sizeof(tarCal);
				memcpy(&tarCal[1], &rva, sizeof(DWORD));
				memcpy(&alloc[szRawSize], tarCal, sizeof(tarCal));

				//Write Ret Code
				rva = (uiRawAddr + szRawSize) - (DWORD)(&alloc[szRawSize + sizeof(tarCal)]) - sizeof(retJmp);
				memcpy(&retJmp[1], &rva, sizeof(DWORD));
				memcpy(&alloc[szRawSize + sizeof(tarCal)], retJmp, sizeof(retJmp));

				return TRUE;
			}
			else
			{
				MessageBoxW(NULL, L"SetHook Failed!!", NULL, NULL);
				return FALSE;
			}
		}

		bool DetourAttachFunc(void* ppRawFunc, void* pNewFunc)
		{
			DetourRestoreAfterWith();
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			LONG erroAttach = DetourAttach((PVOID*)ppRawFunc, pNewFunc);
			LONG erroCommit = DetourTransactionCommit();

			if (erroAttach == NO_ERROR && erroCommit == NO_ERROR) return false;

			MessageBoxW(NULL, L"DetourAttachFunc Failed!!", NULL, NULL);

			return true;
		}

		bool DetourDetachFunc(void* ppRawFunc, void* pNewFunc)
		{
			DetourRestoreAfterWith();
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			LONG erroDetach = DetourDetach((PVOID*)ppRawFunc, pNewFunc);
			LONG erroCommit = DetourTransactionCommit();

			if (erroDetach == NO_ERROR && erroCommit == NO_ERROR) return false;

			MessageBoxW(NULL, L"DetourDetachFunc Failed!!", NULL, NULL);

			return true;
		}
	}
}