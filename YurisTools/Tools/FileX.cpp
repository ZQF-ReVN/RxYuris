#include "FileX.h"

std::string FileX::GetCurrentDirectoryPath()
{
	std::string path;
	CHAR buffer[MAX_PATH] = { 0 };

	GetCurrentDirectoryA(MAX_PATH, buffer);
	path = buffer;
	if (path.empty())
	{
		MessageBoxW(NULL, L"GetCurrentDirectory Failed!!", NULL, NULL);
		return "";
	}
	else
	{
		return path;
	}
}

std::string FileX::BackSlash(LPCSTR lpPath)
{
	std::string path = lpPath;

	for (size_t position = 0; position = path.find('/', position); )
	{
		if (position != std::string::npos)
		{
			path[position] = '\\';
		}
		else
		{
			break;
		}
	}

	return path;
}

std::streamsize FileX::GetFileSize(std::ifstream& fsFile)
{
	std::streamsize szFile = 0;
	std::streampos oldPos = fsFile.tellg();

	fsFile.seekg(0, std::ios::end);
	szFile = fsFile.tellg();
	fsFile.seekg(oldPos, std::ios::beg);

	return szFile;
}