#include "EnumFiles.h"
#include <Windows.h>
#include <queue>


namespace TDA
{
	//EnumFilesA
	EnumFilesA::EnumFilesA(std::string& strBasePath) :m_strBasePath(strBasePath)
	{
		FindFiles(m_strBasePath);
	}

	bool EnumFilesA::FindFiles(std::string strBasePath)
	{
		HANDLE hFind = 0;
		WIN32_FIND_DATAA findData;
		std::string findName;
		std::string directory;
		std::string directoryWildcard;
		std::string nextFindDirectory;
		std::queue<std::string> directoryQueue;


		if (strBasePath[strBasePath.size() - 1] != '\\')
		{
			strBasePath += "\\";
		}
		directoryQueue.push(strBasePath);

		for (; !directoryQueue.empty();)
		{
			directory = directoryQueue.front();
			directoryWildcard = directory + "*";

			hFind = FindFirstFileA(directoryWildcard.c_str(), &findData);
			if (hFind == INVALID_HANDLE_VALUE)
			{
				return FALSE;
			}

			for (;;)
			{
				findName = findData.cFileName;
				if (findData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
				{
					m_vstrAllFileNameRelaPathList.push_back(directory + findName);
				}
				else if ((findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) && (findName != "." && findName != ".."))
				{
					nextFindDirectory = directory + findData.cFileName + "\\";
					directoryQueue.push(nextFindDirectory);
				}

				if (!FindNextFileA(hFind, &findData))
				{
					break;
				}
			}
			directoryQueue.pop();
			FindClose(hFind);
		}

		return TRUE;
	}

	std::vector<std::string>& EnumFilesA::GetAllFilesNameRelaPath()
	{
		return m_vstrAllFileNameRelaPathList;
	}

	std::vector<std::string>& EnumFilesA::GetAllFilesName()
	{
		SIZE_T len = 0;

		for (std::string p : m_vstrAllFileNameRelaPathList)
		{
			len = p.find_last_of("\\") + 1;
			m_vstrAllFileNameList.push_back(p.substr(len, p.length() - len));
		}
		return m_vstrAllFileNameList;
	}

	std::vector<std::string>& EnumFilesA::GetCurrentFilesName()
	{
		for (std::string p : m_vstrAllFileNameRelaPathList)
		{
			if (p.find("\\", 2) == std::string::npos)
			{
				m_vstrCurrentFileNameList.push_back(p.substr(0x2));
			}
		}
		return m_vstrCurrentFileNameList;
	}

	//EnumFilesW
	EnumFilesW::EnumFilesW(std::wstring& strBasePath) :m_strBasePath(strBasePath)
	{
		FindFiles(m_strBasePath);
	}

	bool EnumFilesW::FindFiles(std::wstring strBasePath)
	{
		HANDLE hFind = 0;
		WIN32_FIND_DATAW findData;
		std::wstring findName;
		std::wstring directory;
		std::wstring directoryWildcard;
		std::wstring nextFindDirectory;
		std::queue<std::wstring> directoryQueue;

		if (strBasePath[strBasePath.size() - 1] != L'\\')
		{
			strBasePath += L"\\";
		}
		directoryQueue.push(strBasePath);

		for (; !directoryQueue.empty();)
		{
			directory = directoryQueue.front();
			directoryWildcard = directory + L"*";

			hFind = FindFirstFileW(directoryWildcard.c_str(), &findData);
			if (hFind == INVALID_HANDLE_VALUE)
			{
				return FALSE;
			}

			for (;;)
			{
				findName = findData.cFileName;
				if (findData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE)
				{
					m_vwstrAllFileNameRelaPathList.push_back(directory + findName);
				}
				else if ((findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) && (findName != L"." && findName != L".."))
				{
					nextFindDirectory = directory + findData.cFileName + L"\\";
					directoryQueue.push(nextFindDirectory);
				}

				if (!FindNextFileW(hFind, &findData))
				{
					break;
				}
			}
			directoryQueue.pop();
			FindClose(hFind);
		}

		return TRUE;
	}

	std::vector<std::wstring>& EnumFilesW::GetAllFilesNameRelaPath()
	{
		return m_vwstrAllFileNameRelaPathList;
	}

	std::vector<std::wstring>& EnumFilesW::GetAllFilesName()
	{
		SIZE_T offset = 0;

		for (std::wstring p : m_vwstrAllFileNameRelaPathList)
		{
			offset = p.find_last_of(L"\\") + 1;
			m_vwstrAllFileNameList.push_back(p.substr(offset, p.length() - offset));
		}
		return m_vwstrAllFileNameList;
	}

	std::vector<std::wstring>& EnumFilesW::GetCurrentFilesName()
	{
		for (std::wstring p : m_vwstrAllFileNameRelaPathList)
		{
			if (p.find(L"\\", 2) == std::wstring::npos)
			{
				m_vwstrCurrentFileNameList.push_back(p.substr(0x2));
			}
		}
		return m_vwstrCurrentFileNameList;
	}
}
