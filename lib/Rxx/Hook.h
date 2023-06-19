#pragma once
#include <cstdint>

#include "Hook_API.h"

//Ria's Utility Library X
namespace Rut
{
	namespace HookX
	{
		bool WriteHookCode(uint32_t uiRawAddress, uint32_t uiNewAddress, uint32_t szHookCode);
		bool WriteHookCode_RET(uint32_t uiRawAddress, uint32_t uiRetAddress, uint32_t uiNewAddress);
		bool SetHook(uint32_t uiRawAddr, uint32_t uiTarAddr, uint32_t szRawSize);
		bool DetourAttachFunc(void* ppRawFunc, void* pNewFunc);
		bool DetourDetachFunc(void* ppRawFunc, void* pNewFunc);
	}
}