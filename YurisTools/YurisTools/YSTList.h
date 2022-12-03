#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
#include <shlobj_core.h>
#include "Tools.h"
#include "FileStruct.h"
using namespace ORG_Struct;
using namespace CUS_Struct;

class YSTList
{
private:
    char* m_pYSTList;
    std::wstring m_wsCurrentDir;
    std::wstring m_wsYSTListFile;
    std::vector<ScriptPath> m_vecScriptPathList;
    std::vector<ScriptInfo> m_vecScriptInfoList;

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