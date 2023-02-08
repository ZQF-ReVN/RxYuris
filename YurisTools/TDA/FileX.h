#pragma once
#include <string>
#include <fstream>


namespace TDA
{
	class FileX
	{
	public:
		static bool GetWokrDir(std::wstring& wsDir, const wchar_t* lpApendDir);
		static std::string GetCurrentDirectoryPath();
		static std::string BackSlash(const char* lpPath);
		static void BackSlash(std::string& strPath, const char* lpPath);
		static bool PathRemoveFileName(std::wstring& wsPath, std::wstring& wsDir);

		template <typename FSTREAM>
		static std::streamsize GetFileSize(FSTREAM& fsFile)
		{
			std::streamsize szFile = 0;
			std::streampos oldPos = fsFile.tellg();

			fsFile.seekg(0, std::ios::end);
			szFile = fsFile.tellg();
			fsFile.seekg(oldPos, std::ios::beg);

			return szFile;
		}

	};
}

