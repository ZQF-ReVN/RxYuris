#pragma once
#include <Windows.h>
#include <string>
#include <fstream>

class FileX
{
public:
	static std::string GetCurrentDirectoryPath();
	static std::string BackSlash(LPCSTR lpPath);
	static std::streamsize GetFileSize(std::ifstream& fsFile);

};