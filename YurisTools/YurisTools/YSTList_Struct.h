#pragma once
#include <string>

namespace YSTList_Struct
{
    //from https://github.com/arcusmaximus/VNTranslationTools/blob/main/VNTextPatch.Shared/Scripts/Yuris/Notes.txt

    /*
    * YSTLFile_V5
    * {
    *   YSTListHeader
    *   ScriptInfo[YSTListHeader.iScriptCount]
    * }
    */
    struct YSTListHeader_V5
    {
        char aSignature[4]; //YSTL
        int iVersion;
        int iScriptCount;
        //ScriptInfo_V5[iScriptCount];
    };

    struct ScriptInfo_V5
    {
        int iIndex;
        int iPathLength;
        //char PathName[iPathLength];
        int iHighDateTime;
        int iLowDateTime;
        int iVariableCount;
        int iLabelCount;
        int iTextCount;
        char* lpPath; //Not part of the original
    };

    /*
    * YSTLFile_V2
    * {
    *   YSTListHeader
    *   ScriptInfo_V2[YSTListHeader.iScriptCount]
    * }
    */
    struct YSTListHeader_V2
    {
        char aSignature[4]; //YSTL
        int iVersion;
        int iScriptCount;
        //ScriptInfo_V2[iScriptCount];
    };

    struct ScriptInfo_V2
    {
        int iIndex;
        int iPathLength;
        //char PathName[iPathLength];
        int iHighDateTime;
        int iLowDateTime;
        int iUnknow00;
        int iUnknow01;
        char* lpPath; //Not part of the original
    };

    struct ScriptPath
    {
        std::wstring wsYbn;
        std::wstring wsPath;
        int iTextCount;
    };
}
