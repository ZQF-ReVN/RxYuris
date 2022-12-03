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
using namespace Cus_Struct;

class YstList
{
private:
    char* m_pYstList;
    std::wstring m_wsCurrentDir;
    std::wstring m_wsYstListFile;
    std::vector<ScriptPath> m_vecScriptPathList;
    std::vector<ScriptInfo> m_vecScriptInfoList;

private:
    bool GetScriptInfo();
    void GetMakeDirInfo();

public:
    YstList(std::wstring wsYstListFile);
    ~YstList();

    void MakeDir();
    void RestoreDir();
    void TextCount();
};