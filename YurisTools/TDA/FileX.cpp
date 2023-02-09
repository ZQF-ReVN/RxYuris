#include "FileX.h"

#include <Windows.h>


namespace TDA
{
	bool FileX::GetWokrDir(std::wstring& wsDir, const wchar_t* lpApendDir)
	{
		wsDir.resize(MAX_PATH);
		DWORD szWorkDir = GetCurrentDirectoryW(MAX_PATH, const_cast<wchar_t*>(wsDir.data()));
		if (szWorkDir < MAX_PATH)
		{
			wsDir.resize(szWorkDir);
			if (lpApendDir)
			{
				wsDir.append(lpApendDir);
			}

			return true;
		}
		else
		{
			return false;
		}
	}

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

	std::string FileX::BackSlash(const char* lpPath)
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

	void FileX::BackSlash(std::string& strPath, const char* lpPath)
	{
		strPath = lpPath;

		for (size_t position = 0; position = strPath.find('/', position); )
		{
			if (position != std::string::npos)
			{
				strPath[position] = '\\';
			}
			else
			{
				break;
			}
		}
	}

	bool FileX::PathRemoveFileName(std::wstring& wsPath, std::wstring& wsDir)
	{
		size_t pos = wsPath.rfind(L"\\");
		if (pos != std::wstring::npos)
		{
			wsDir = wsPath.substr(0, pos + 1);

			return true;
		}
		else
		{
			return false;
		}
	}
}

