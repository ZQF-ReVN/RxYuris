#pragma once
#include <vector>
#include <fstream>
#include "YSTList_Struct.h"

class YSTList
{
private:
    std::wstring m_wsYSTList;
    std::ifstream m_ifsYSTlist;
    YSTList_Struct::YSTListHeader_V2 m_Header;
    std::vector<YSTList_Struct::YSTListEntry_V5> m_vecEntry;

private:
    bool InitIndex();

public:
    YSTList(std::wstring wsYSTList);
    ~YSTList();

    bool PrintIndexToFile();
    bool MakeDirStructure();
};