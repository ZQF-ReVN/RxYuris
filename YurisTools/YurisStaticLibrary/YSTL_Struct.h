#pragma once
#include <string>


namespace YurisStaticLibrary
{
    namespace YSTL_Struct
    {
        //from https://github.com/arcusmaximus/VNTranslationTools/blob/main/VNTextPatch.Shared/Scripts/Yuris/Notes.txt

        /*
        * YSTLFile_V2
        * {
        *   YSTLHeader_V2
        *   YSTLEntry_V2[YSTListHeader_V2.iScriptCount]
        * }
        */
        struct YSTLHeader_V2
        {
            char aSignature[4];               // YSTL
            unsigned int uiVersion;
            unsigned int uiEntryCount;
        };

        struct YSTLEntry_V2
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
        *   YSTLHeader_V2
        *   YSTLEntry_V5[YSTLHeader_V2.iScriptCount]
        * }
        */
        struct YSTLEntry_V5
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
}
