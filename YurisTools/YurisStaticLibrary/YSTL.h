#pragma once
#include <vector>
#include <fstream>
#include "YSTL_Struct.h"


namespace YurisStaticLibrary
{
    class YSTL
    {
    private:
        std::wstring m_wsYSTL;
        std::ifstream m_ifsYSTL;
        YSTL_Struct::YSTLHeader_V2 m_Header;
        std::vector<YSTL_Struct::YSTLEntry_V5> m_vecEntry;

    private:
        bool InitIndex();

    public:
        YSTL(std::wstring wsYSTL);
        ~YSTL();

        bool PrintIndexToFile();
        bool MakeStructure();
        bool BackStructure();
    };
}
