#include "Hook_API.h"
#include "Hook.h"
#include "Hook_API_DEF.h"

#include <Windows.h>


namespace Rut
{
	namespace HookX
	{
		//*********Start Hook CreateFontA*******
		static DWORD sg_dwCharSet = 0;
		static LPCSTR sg_lpFontName = nullptr;
		static pCreateFontA rawCreateFontA = CreateFontA;
		HFONT WINAPI newCreateFontA(INT cHeight, INT cWidth, INT cEscapement, INT cOrientation, INT cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily, LPCSTR pszFaceName)
		{
			iCharSet = sg_dwCharSet;
			pszFaceName = sg_lpFontName;
			return rawCreateFontA(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
		}

		bool HookCreateFontA(const uint32_t uiCharSet, const char* cpFontName)
		{
			sg_dwCharSet = uiCharSet;
			sg_lpFontName = cpFontName;
			return DetourAttachFunc(&rawCreateFontA, newCreateFontA);
		}
		//*********END Hook CreateFontA*********


		//*********Start Hook CreateFontIndirectA*******
		static pCreateFontIndirectA rawCreateFontIndirectA = CreateFontIndirectA;
		HFONT WINAPI newCreateFontIndirectA(LOGFONTA* lplf)
		{
			lplf->lfCharSet = (BYTE)sg_dwCharSet;
			strcpy_s(lplf->lfFaceName, sg_lpFontName);
			return rawCreateFontIndirectA(lplf);
		}

		bool HookCreateFontIndirectA(const uint32_t uiCharSet, const char* cpFontName)
		{
			sg_dwCharSet = uiCharSet;
			sg_lpFontName = cpFontName;
			return DetourAttachFunc(&rawCreateFontIndirectA, newCreateFontIndirectA);
		}
		//*********END Hook CreateFontIndirectA*********


		//*********Start Hook CreateWindowExA*******
		static LPCSTR sg_lpNewTitle = nullptr;
		static LPCSTR sg_lpRawTitle = nullptr;
		static pCreateWindowExA RawCreateWindowExA = CreateWindowExA;
		HWND WINAPI NewCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, INT X, INT Y, INT nWidth, INT nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
		{
			if (!lstrcmpA(lpWindowName, sg_lpRawTitle))
			{
				lpWindowName = sg_lpNewTitle;
				DetourDetachFunc(&RawCreateWindowExA, &NewCreateWindowExA);
			}

			return RawCreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
		}

		bool HookTitleExA(const char* cpRawTitle, const char* cpPatchTitle)
		{
			sg_lpNewTitle = cpPatchTitle;
			sg_lpRawTitle = cpRawTitle;
			return DetourAttachFunc(&RawCreateWindowExA, NewCreateWindowExA);
		}
		//*********END Hook CreateWindowExA*********
	}
}