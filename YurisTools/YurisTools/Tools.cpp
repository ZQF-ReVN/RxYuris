#include "Tools.h"

unsigned int Tools::GetFileSize(std::ifstream& fsFile)
{
	std::streamoff szFile = 0;
	std::streamoff oldOff = fsFile.tellg();

	fsFile.seekg(0, std::ios::end);
	szFile = fsFile.tellg();
	fsFile.seekg(oldOff, std::ios::beg);

	return (unsigned int)szFile;
}

std::wstring Tools::StrToWStr(std::string& strString, UINT uCodePage)
{
	unsigned int lenWStr = 0;
	std::wstring result;

	lenWStr = MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), NULL, NULL);
	wchar_t* buffer = new wchar_t[lenWStr + 1];
	MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), buffer, lenWStr);
	buffer[lenWStr] = '\0';

	result.append(buffer);
	delete[] buffer;
	return result;
}
