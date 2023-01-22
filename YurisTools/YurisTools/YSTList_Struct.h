#pragma once
#include <string>

namespace YSTList_Struct
{
    //from https://github.com/arcusmaximus/VNTranslationTools/blob/main/VNTextPatch.Shared/Scripts/Yuris/Notes.txt

    /*
    * YSTLFile_V2
    * {
    *   YSTListHeader_V2
    *   YSTListEntry_V2[YSTListHeader_V2.iScriptCount]
    * }
    */
    struct YSTListHeader_V2
    {
        char aSignature[4];               // YSTL
        unsigned int uiVersion;
        unsigned int uiEntryCount;
    };

    struct YSTListEntry_V2
    {
        unsigned int uiSequence;
        unsigned int szRelativePath;
        char aRelativePath[256];          // aRelativePath[szRelativePath]
        unsigned int uiHighDateTime;
        unsigned int uiLowDateTime;
        unsigned int uiUnknow00;
        unsigned int uiUnknow01;
    };


    /*
    * YSTLFile_V5
    * {
    *   YSTListHeader_V2
    *   YSTListEntry_V5[YSTListHeader_V2.iScriptCount]
    * }
    */
    struct YSTListEntry_V5
    {
        unsigned int uiSequence;
        unsigned int szRelativePath;
        char aRelativePath[256];          // uiPathLength[szRelativePath]
        unsigned int uiHighDateTime;
        unsigned int uiLowDateTime;
        unsigned int uiVariableCount;
        unsigned int uiLabelCount;
        unsigned int uiTextCount;
    };
}
