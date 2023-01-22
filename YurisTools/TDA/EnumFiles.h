#pragma once
#include <string>
#include <vector>


namespace TDA
{
	class EnumFilesA
	{
	public:
		EnumFilesA(std::string& strBasePath);

		std::vector<std::string>& GetAllFilesName();
		std::vector<std::string>& GetAllFilesNameRelaPath();
		std::vector<std::string>& GetCurrentFilesName();
	private:
		bool FindFiles(std::string);

		std::string m_strBasePath;
		std::vector<std::string> m_vstrAllFileNameList;
		std::vector<std::string> m_vstrAllFileNameRelaPathList;
		std::vector<std::string> m_vstrCurrentFileNameList;
	};

	class EnumFilesW
	{
	public:
		EnumFilesW(std::wstring& strBasePath);

		std::vector<std::wstring>& GetAllFilesName();
		std::vector<std::wstring>& GetAllFilesNameRelaPath();
		std::vector<std::wstring>& GetCurrentFilesName();
	private:
		bool FindFiles(std::wstring);

		std::wstring m_strBasePath;
		std::vector<std::wstring> m_vwstrAllFileNameList;
		std::vector<std::wstring> m_vwstrAllFileNameRelaPathList;
		std::vector<std::wstring> m_vwstrCurrentFileNameList;
	};
}

