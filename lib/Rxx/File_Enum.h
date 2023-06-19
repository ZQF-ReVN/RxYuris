#pragma once
#include <vector>
#include <string>

//Ria's Utility Library X
namespace Rut
{
	namespace FileX
	{
		bool GetAllFilesPathA(std::string msBasePath, std::vector<std::string>& vecList);
		bool GetAllFilesPathW(std::wstring wsBasePath, std::vector<std::wstring>& vecList);

		bool GetAllFileNameA(std::string msBasePath, std::vector<std::string>& vecList);
		bool GetAllFileNameW(std::wstring wsBasePath, std::vector<std::wstring>& vecList);
	}
}

