#pragma once
#include <cstdint>

//Ria's Utility Library X
namespace Rut
{
	namespace HookX
	{
		bool HookCreateFontA(const uint32_t uiCharSet, const char* cpFontName);
		bool HookCreateFontIndirectA(const uint32_t uiCharSet, const char* cpFontName);
		bool HookTitleExA(const char* cpRawTitle, const char* cpPatchTitle);
	}
}