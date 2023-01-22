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
		static std::streamsize GetFileSize(std::ifstream& fsFile);

	};
}

