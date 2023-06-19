#include "Str.h"

#include <codecvt>
#include <Windows.h>


namespace Rut
{
	namespace StrX
	{
		std::locale& GetCVT_UTF8()
		{
			static std::locale cvtUTF8 = std::locale
			(
				std::locale::empty(),
				new std::codecvt_utf8
				<wchar_t, 0x10ffff, std::codecvt_mode(std::consume_header | std::generate_header | std::little_endian)>
			);
			return cvtUTF8;
		}

		std::wstring StrToWStr(const std::string& msString, size_t uCodePage)
		{
			std::wstring wsString;
			if (StrToWStr(msString, wsString, uCodePage) == 0)
			{
				wsString.clear();
			}
			return wsString;
		}

		std::string WStrToStr(const std::wstring& wsString, size_t uCodePage)
		{
			std::string msString;
			if (WStrToStr(wsString, msString, uCodePage) == 0)
			{
				msString.clear();
			}
			return msString;
		}

		size_t StrToWStr(const std::string& msString, std::wstring& wsString, size_t uCodePage)
		{
			int charCount = MultiByteToWideChar
			(
				uCodePage, NULL, msString.c_str(), static_cast<int>(msString.size()), NULL, NULL
			);

			if (charCount == 0) { wsString = L""; return 0; }

			wsString.resize(charCount);

			MultiByteToWideChar
			(
				uCodePage, NULL, msString.c_str(), static_cast<int>(msString.size()), const_cast<wchar_t*>(wsString.data()), charCount
			);

			return charCount;
		}

		size_t WStrToStr(const std::wstring& wsString, std::string& msString, size_t uCodePage)
		{
			int wcharCount = WideCharToMultiByte
			(
				uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), NULL, NULL, NULL, NULL
			);

			if (wcharCount == 0) { msString = ""; return 0; }

			msString.resize(wcharCount);

			WideCharToMultiByte
			(
				uCodePage, NULL, wsString.c_str(), static_cast<int>(wsString.size()), const_cast<char*>(msString.data()), wcharCount, NULL, NULL
			);

			return wcharCount;
		}

		std::wstring StrToWStr_CVT(const std::string& msString, size_t uCodePage)
		{
			std::wstring wsString;
			StrToWStr_CVT(msString, wsString, uCodePage);
			return wsString;
		}

		std::string WStrToStr_CVT(const std::wstring& wsString, size_t uCodePage)
		{
			std::string msString;
			WStrToStr_CVT(wsString, msString, uCodePage);
			return msString;
		}

		//Essentially it is still call MultiByteToWideChar / WideCharToMultiByte
		void StrToWStr_CVT(const std::string& msString, std::wstring& wsString, size_t uCodePage)
		{
			std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString
			(
				new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage))
			);
			wsString = cvtString.from_bytes(msString);
		}

		void WStrToStr_CVT(const std::wstring& wsString, std::string& msString, size_t uCodePage)
		{
			std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cvtString
			(
				new std::codecvt_byname<wchar_t, char, mbstate_t>('.' + std::to_string(uCodePage))
			);
			msString = cvtString.to_bytes(wsString);
		}
	}
}