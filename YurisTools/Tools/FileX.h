#pragma once
#include <string>
#include <fstream>

class FileX
{
public:
	static std::string GetCurrentDirectoryPath();
	static std::string BackSlash(const char* lpPath);
	static void BackSlash(std::string& strPath, const char* lpPath);
	static std::streamsize GetFileSize(std::ifstream& fsFile);

};