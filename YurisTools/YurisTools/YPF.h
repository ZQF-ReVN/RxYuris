#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "YPF_Struct.h"

class YPF
{
private:
	std::wstring m_wsYPF;
	std::ifstream m_ifsYPF;
	YPF_Struct::YPFHeader_V2 m_Header;
	YPF_Struct::YPFEntry_V5 m_Entry;
	std::vector<YPF_Struct::YPFEntry_V5> m_vecEntry;

	void InitIndex();
	static unsigned char GetNameSize(unsigned char szEncName);
	static void DecodeName(char* lpEncName, size_t szName);

public:
	YPF(std::wstring wsFile);
	~YPF();

	void DecodeFile();

private:

};