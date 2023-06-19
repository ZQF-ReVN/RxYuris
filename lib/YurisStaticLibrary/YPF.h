#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "YPF_Struct.h"


namespace YurisLibrary
{
	class YPF
	{
	private:
		std::wstring m_wsYPF;
		std::ifstream m_ifsYPF;
		YPF_Struct::YPFHeader_V2 m_Header;
		std::vector<YPF_Struct::YPFEntry_V5> m_vecEntry;

		void InitIndex();
		static unsigned char DecodePathSize(unsigned char szEncRelativePath);
		static void DecodePathName(char* lpEncRelativePath, size_t szEncRelativePath);

	public:
		YPF(std::wstring wsFile);
		~YPF();

		//用于处理屋子对YPF的加密
		void DecodeFile_WZ();

	private:

	};
}

