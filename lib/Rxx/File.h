#pragma once
#include <string>

#include "String.h"
#include "File_Enum.h"
#include "File_Stream.hpp"

//Ria's Utility Library X
namespace Rut
{
	namespace FileX
	{
		void         SaveFileViaPath(const char* cpPath, void* pData, size_t nBytes);
		void         SaveFileViaPath(const wchar_t* wpPath, void* pData, size_t nBytes);
		void         SaveFileViaPath(std::wstring& wsPath, void* pData, size_t nBytes);
		void         SaveFileViaPath(std::string& msPath, void* pData, size_t nBytes);

		size_t		 GetModuleNameViaBase_Ptr(char* cpBuf, uint32_t uiBase);
		size_t		 GetModuleNameViaBase_Ptr(wchar_t* wpBuf, uint32_t uiBase);
		std::string  GetModuleNameViaBaseA(uint32_t uiBase);
		std::wstring GetModuleNameViaBaseW(uint32_t uiBase);

		size_t       GetCurrentDir_Ptr(char* pPath);
		size_t       GetCurrentDir_Ptr(wchar_t* pPath);
		std::string  GetCurrentDirA();
		std::wstring GetCurrentDirW();


		char*		 FormatSlash_Ptr(char* cpPath, char cSlash);
		wchar_t*	 FormatSlash_Ptr(wchar_t* wpPath, wchar_t wcSlash);
		std::string  FormatSlash(const std::string& msPath, char cSlash);
		std::wstring FormatSlash(const std::wstring& wsPath, wchar_t wcSlash);


		size_t		 PathRemoveFileName_Ptr(char* cpPath);
		size_t		 PathRemoveFileName_Ptr(wchar_t* wpPath);
		void		 PathRemoveFileName_Ref(std::string& msPath);
		void		 PathRemoveFileName_Ref(std::wstring& wsPath);
		std::wstring PathRemoveFileName(std::wstring sPath);
		std::string  PathRemoveFileName(std::string msPath);


		size_t		 PathRemoveExtension_Ptr(char* cpPath);
		size_t		 PathRemoveExtension_Ptr(wchar_t* wpPath);
		void		 PathRemoveExtension_Ref(std::string& msPath);
		void		 PathRemoveExtension_Ref(std::wstring& wsPath);
		std::string	 PathRemoveExtension(std::string msPath);
		std::wstring PathRemoveExtension(std::wstring wsPath);


		size_t       PathGetFileName_Ptr(char* cpPath);
		size_t       PathGetFileName_Ptr(wchar_t* wpPath);
		void		 PathGetFileName_Ref(std::string& msPath);
		void		 PathGetFileName_Ref(std::wstring& wsPath);
		std::string  PathGetFileName(std::string msPath);
		std::wstring PathGetFileName(std::wstring wsPath);
	}
}

