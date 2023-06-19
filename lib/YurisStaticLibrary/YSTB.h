#pragma once
#include <string>
#include <fstream>

#include "YSTB_Struct.h"


namespace YurisLibrary
{
	class YSTB
	{
	public:
		static bool TextInset_V2(std::wstring wsFileName, unsigned int uiCodePage);
		static bool TextDump_V2(std::wstring wsFileName, unsigned int uiCodePage, bool isAudioFileName);
		static bool XorScript(std::string strYSTB, unsigned char* aXorKey);
		static void GuessXorKey(std::string strYSTB, unsigned char* aXorKey);

	};
}
