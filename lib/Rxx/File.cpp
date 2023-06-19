#include "File.h"

#include <Windows.h>
#include <shlobj.h>
#include <stdexcept>

using namespace Rut::StrX;


namespace Rut
{
	namespace FileX
	{
		void SaveFileViaPath(const wchar_t* wpPath, void* pData, size_t nBytes)
		{
			std::wstring dir = PathRemoveFileName(GetCurrentDirW() + wpPath);
			FormatSlash_Ptr((wchar_t*)dir.c_str(), L'\\');
			SHCreateDirectoryExW(NULL, dir.c_str(), NULL);

			HANDLE hfile = CreateFileW(wpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hfile == INVALID_HANDLE_VALUE) { throw std::runtime_error("SaveFileViaRelaPath: Create File Error!"); }

			WriteFile(hfile, pData, nBytes, NULL, NULL);
			FlushFileBuffers(hfile);
			CloseHandle(hfile);
		}

		void SaveFileViaPath(const char* cpPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(StrToWStr(cpPath, CP_ACP).c_str(), pData, nBytes);
		}

		void SaveFileViaPath(std::wstring& wsPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(wsPath.c_str(), pData, nBytes);
		}

		void SaveFileViaPath(std::string& msPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(msPath.c_str(), pData, nBytes);
		}


		size_t GetModuleNameViaBase_Ptr(char* cpBuf, uint32_t uiBase)
		{
			GetModuleFileNameA((HMODULE)uiBase, cpBuf, MAX_PATH);
			return PathGetFileName_Ptr(cpBuf);
		}

		size_t GetModuleNameViaBase_Ptr(wchar_t* wpBuf, uint32_t uiBase)
		{
			GetModuleFileNameW((HMODULE)uiBase, wpBuf, MAX_PATH);
			return PathGetFileName_Ptr(wpBuf);
		}

		std::string GetModuleNameViaBaseA(uint32_t uiBase)
		{
			std::string name;
			name.resize(MAX_PATH);
			name.resize(GetModuleNameViaBase_Ptr((char*)name.c_str(), uiBase));
			return name;
		}

		std::wstring GetModuleNameViaBaseW(uint32_t uiBase)
		{
			std::wstring name;
			name.resize(MAX_PATH);
			name.resize(GetModuleNameViaBase_Ptr((wchar_t*)name.c_str(), uiBase));
			return name;
		}


		size_t GetCurrentDir_Ptr(char* pPath)
		{
			size_t size = GetCurrentDirectoryA(MAX_PATH, pPath);
			memcpy(pPath + size, "\\", 2);
			return ++size;
		}

		size_t GetCurrentDir_Ptr(wchar_t* pPath)
		{
			size_t size = GetCurrentDirectoryW(MAX_PATH, pPath);
			memcpy(pPath + size, L"\\", 4);
			return ++size;
		}

		std::string GetCurrentDirA()
		{
			char tmp[MAX_PATH] = { 0 };
			size_t sz = GetCurrentDir_Ptr(tmp);
			std::string path;
			path.resize(sz);
			memcpy((void*)path.c_str(), tmp, sz);
			return path;
		}

		std::wstring GetCurrentDirW()
		{
			wchar_t tmp[MAX_PATH] = { 0 };
			size_t sz = GetCurrentDir_Ptr(tmp);
			std::wstring path;
			path.resize(sz);
			memcpy((void*)path.c_str(), tmp, sz * 2);
			return path;
		}


		char* FormatSlash_Ptr(char* cpPath, char cSlash)
		{
			switch (cSlash)
			{
			case '\\': 
			{
				for (size_t ite = 0; cpPath[ite]; ite++)
				{
					if ((uint8_t)cpPath[ite] > 0x7F) { ite++; continue; }

					if (cpPath[ite] == '/') { cpPath[ite] = '\\'; }
				}
			}
			break;

			case '/':
			{
				for (size_t ite = 0; cpPath[ite]; ite++)
				{
					if ((uint8_t)cpPath[ite] > 0x7F) { ite++; continue; }

					if (cpPath[ite] == '\\') { cpPath[ite] = '/'; }
				}
			}
			break;
			}

			return cpPath;
		}

		wchar_t* FormatSlash_Ptr(wchar_t* wpPath, wchar_t wcSlash)
		{
			switch (wcSlash)
			{
			case L'\\':
			{
				for (size_t ite = 0; wpPath[ite]; ite++)
				{
					if (wpPath[ite] == L'/') { wpPath[ite] = L'\\';}
				}
			}
			break;

			case L'/':
			{
				for (size_t ite = 0; wpPath[ite]; ite++)
				{
					if (wpPath[ite] == L'\\') { wpPath[ite] = L'/'; }
				}
			}
			break;
			}

			return wpPath;
		}

		std::string FormatSlash(const std::string& msPath, char cSlash)
		{
			FormatSlash_Ptr(const_cast<char*>(msPath.data()), cSlash);
			return msPath;
		}

		std::wstring FormatSlash(const std::wstring& wsPath, wchar_t wcSlash)
		{
			FormatSlash_Ptr(const_cast<wchar_t*>(wsPath.data()), wcSlash);
			return wsPath;
		}


		size_t PathRemoveFileName_Ptr(char* cpPath)
		{
			size_t len = strlen(cpPath);

			for (size_t ite_char = len - 1; ite_char > 0; ite_char--)
			{
				if (cpPath[ite_char] == '\\')
				{
					if (cpPath[ite_char - 1] <= 0x7F)
					{
						cpPath[ite_char + 1] = '\0';
						return ite_char + 1;
					}
				}

				if (cpPath[ite_char] == '/')
				{
					if (cpPath[ite_char - 1] <= 0x7F)
					{
						cpPath[ite_char + 1] = L'\0';
						return ite_char + 1;
					}
				}
			}

			return len;
		}

		size_t PathRemoveFileName_Ptr(wchar_t* wpPath)
		{
			size_t len = wcslen(wpPath);

			for (size_t ite_char = len - 1; ite_char > 0; ite_char--)
			{
				if (wpPath[ite_char] == L'\\')
				{
					wpPath[ite_char + 1] = L'\0';
					return ite_char + 1;
				}

				if (wpPath[ite_char] == L'/')
				{
					wpPath[ite_char + 1] = L'\0';
					return ite_char + 1;
				}
			}

			return len;
		}

		void PathRemoveFileName_Ref(std::string& msPath)
		{
			msPath.resize(PathRemoveFileName_Ptr((char*)msPath.c_str()));
		}

		void PathRemoveFileName_Ref(std::wstring& wsPath)
		{
			wsPath.resize(PathRemoveFileName_Ptr((wchar_t*)wsPath.c_str()));
		}

		std::string PathRemoveFileName(std::string msPath)
		{
			msPath.resize(PathRemoveFileName_Ptr((char*)msPath.c_str()));
			return msPath;
		}

		std::wstring PathRemoveFileName(std::wstring wsPath)
		{
			wsPath.resize(PathRemoveFileName_Ptr((wchar_t*)wsPath.c_str()));
			return wsPath;
		}


		size_t PathRemoveExtension_Ptr(char* cpPath)
		{
			size_t len = strlen(cpPath);

			for (size_t ite_char = len - 1; ite_char > 0; ite_char--)
			{
				if (cpPath[ite_char] == '.')
				{
					cpPath[ite_char] = '\0';
					return ite_char;
				}
			}

			return len;
		}

		size_t PathRemoveExtension_Ptr(wchar_t* wpPath)
		{
			size_t len = wcslen(wpPath);

			for (size_t ite_char = len - 1; ite_char > 0; ite_char--)
			{
				if (wpPath[ite_char] == L'.')
				{
					wpPath[ite_char] = L'\0';
					return ite_char;
				}
			}

			return len;
		}

		void PathRemoveExtension_Ref(std::string& msPath)
		{
			msPath.resize(PathRemoveExtension_Ptr((char*)msPath.c_str()));
		}

		void PathRemoveExtension_Ref(std::wstring& wsPath)
		{
			wsPath.resize(PathRemoveExtension_Ptr((wchar_t*)wsPath.c_str()));
		}

		std::string PathRemoveExtension(std::string msPath)
		{
			msPath.resize(PathRemoveExtension_Ptr((char*)msPath.c_str()));
			return msPath;
		}

		std::wstring PathRemoveExtension(std::wstring wsPath)
		{
			wsPath.resize(PathRemoveExtension_Ptr((wchar_t*)wsPath.c_str()));
			return wsPath;
		}


		size_t PathGetFileName_Ptr(char* cpPath)
		{
			size_t len = strlen(cpPath);

			for (size_t iteChar = len - 1; iteChar > 0; iteChar--)
			{
				if (cpPath[iteChar] != '\\' && cpPath[iteChar] != '/')
				{
					continue;
				}

				if (cpPath[iteChar - 1] <= 0x7F)
				{
					size_t name_len = len - iteChar - 1;
					memcpy(cpPath, cpPath + iteChar + 1, name_len);
					cpPath[name_len] = '\0';
					return name_len;
				}
			}

			return len;
		}

		size_t PathGetFileName_Ptr(wchar_t* wpPath)
		{
			size_t len = wcslen(wpPath);

			for (size_t iteChar = len - 1; iteChar > 0; iteChar--)
			{
				if (wpPath[iteChar] != L'\\' && wpPath[iteChar] != L'/')
				{
					continue;
				}

				size_t name_len = len - iteChar - 1;
				memcpy(wpPath, wpPath + iteChar + 1, name_len * 2);
				wpPath[name_len] = L'\0';
				return name_len;
			}

			return len;
		}

		void PathGetFileName_Ref(std::string& msPath)
		{
			msPath.resize(PathGetFileName_Ptr((char*)msPath.data()));
		}

		void PathGetFileName_Ref(std::wstring& wsPath)
		{
			wsPath.resize(PathGetFileName_Ptr((wchar_t*)wsPath.data()));
		}

		std::string PathGetFileName(std::string msPath)
		{
			msPath.resize(PathGetFileName_Ptr((char*)msPath.c_str()));
			return msPath;
		}

		std::wstring PathGetFileName(std::wstring wsPath)
		{
			wsPath.resize(PathGetFileName_Ptr((wchar_t*)wsPath.c_str()));
			return wsPath;
		}
	}
}