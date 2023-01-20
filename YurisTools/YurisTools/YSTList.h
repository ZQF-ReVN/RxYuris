#pragma once
#include <vector>
#include "YSTList_Struct.h"

class YSTList
{
private:
    char* m_pYSTList;
    std::wstring m_wsCurrentDir;
    std::wstring m_wsYSTListFile;
    std::vector<YSTList_Stuct::ScriptPath> m_vecScriptPathList;
    std::vector<YSTList_Stuct::ScriptInfo_V5> m_vecScriptInfoList;

private:
    bool GetScriptInfo();
    void GetMakeDirInfo();

public:
    YSTList(std::wstring wsYSTListFile);
    ~YSTList();

    void MakeDir();
    void RestoreDir();
    void TextCount();
};