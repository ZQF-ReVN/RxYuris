#pragma once
#include <iostream>

//************************
//*  Original structure  *
//************************
namespace ORG_Struct
{
    //from https://github.com/arcusmaximus/VNTranslationTools/blob/main/VNTextPatch.Shared/Scripts/Yuris/Notes.txt

    /*
    * YSTLFile
    * {
    *   YSTListHeader
    *   ScriptInfo[YSTListHeader.iScriptCount]
    * }
    */
    struct YSTListHeader
    {
        char aSignature[4]; //YSTL
        int iVersion;
        int iScriptCount;
        //ScriptInfo[iScriptCount];
    };

    struct ScriptInfo
    {
        int iIndex;
        int iPathLength;
        //char PathName[iPathLength];
        int iLowDateTime;
        int iHighDateTime;
        int iVariableCount;
        int iLabelCount;
        int iTextCount;
        char* lpPath; //Not part of the original
    };


    /*
    * YSTBFile_V5
    * {
    *   YSTBHeader
    *   Instruction[iInstructionCount]
    *   AttributeDescriptor[iAttributeDescriptorsSize / 12]
    *   AttributeValues[iAttributeDescriptorsSize / Indeterminate]
    *   lineNumbers[iLineNumbersSize / 4]
    * }
    */
    struct YSTBHeader_V5
    {
        char aSignature[4]; //YSTB
        int iVersion; //300 - 
        int iInstructionCount;
        int iInstructionsSize; //iInstructionCount * 4
        int iAttributeDescriptorsSize;
        int iAttributeValuesSize;
        int iLineNumbersSize;
        int iPadding;
    };

    struct YSTBHeader_V2
    {
        char aSignature[4]; //YSTB
        int iVersion; //224 - 300
        int iCodeSegSize;
        int iResSegSize;
        int iResOffset;
        int iReserved0;
        int iReserved1;
        int iReserved2;
    };

    struct Instruction
    {
        unsigned char ucOpcode;
        unsigned char ucAttributeCount;
        unsigned char ucUnknow ;
        unsigned char ucPadding;
    };

    struct AttributeDescriptor
    {
        short sID;
        short sType; //(1 = long, 2 = double, 3 = string)
        int iSize;
        int iOffset;
    };
    //4D XX XX 22 ... 22      pushstring(quoted string with support for \\, \nand \t escape codes, but not \" or \')
}

//************************
//* Customized structure *
//************************
namespace CUS_Struct
{
    struct ScriptPath
    {
        std::wstring wsYbn;
        std::wstring wsPath;
        int iTextCount;
    };
}


