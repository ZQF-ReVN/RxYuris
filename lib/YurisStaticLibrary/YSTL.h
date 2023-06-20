#pragma once
#include <vector>
#include <fstream>
#include "YSTL_Struct.h"


namespace YurisLibrary
{
    namespace YSTL
    {
        class YSTL_V5
        {
        private:
            std::wstring m_wsYSTL;
            std::ifstream m_ifsYSTL;
            YSTLHeader_V2 m_Header;
            std::vector<YSTLEntry_V5> m_vecEntry;

        private:
            bool InitIndex();

        public:
            YSTL_V5(std::wstring wsYSTL);
            ~YSTL_V5();

            bool PrintIndexToFile();
            bool MakeStructure();
            bool BackStructure();
        };
    }
}
