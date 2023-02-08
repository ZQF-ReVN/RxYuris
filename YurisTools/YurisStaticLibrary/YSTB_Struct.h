#pragma once


namespace YurisStaticLibrary
{
    namespace YSTB_Struct
    {
        /*
        * YSTBFile_V5
        * {
        *   YSTBHeader_V5
        *   Instruction_V5[iInstructionCount]
        *   AttributeDescriptor_V5[iAttributeDescriptorsSize / 12]
        *   AttributeValues_V5[iAttributeDescriptorsSize / Indeterminate]
        *   lineNumbers_V5[iLineNumbersSize / 4]
        * }
        */
        struct YSTBHeader_V5
        {
            unsigned char aSignature[4]; //YSTB
            unsigned int uiVersion; //300 - 
            unsigned int uiInstructionCount;
            unsigned int uiInstructionsSize; //iInstructionCount * 4
            unsigned int uiAttributeDescriptorsSize;
            unsigned int uiAttributeValuesSize;
            unsigned int uiLineNumbersSize;
            unsigned int uiPadding;
        };

        struct Instruction_V5
        {
            unsigned char ucOpcode;
            unsigned char ucAttributeCount;
            unsigned char ucUnknow;
            unsigned char ucPadding;
        };

        struct AttributeDescriptor_V5
        {
            short sID;
            short sType; //(1 = long, 2 = double, 3 = string)
            int iSize;
            int iOffset;
        };
        //4D XX XX 22 ... 22      pushstring(quoted string with support for \\, \nand \t escape codes, but not \" or \')

        /*
        * YSTBFile_V2
        * {
        *   YSTBHeader_V2
        *    CodeSegment
        *       Instruction_V2[?]
        *          ResEntry_V2[?]
        *    ResSegment
        *       ResInfo_V2[?]
        * }
        */
        struct YSTBHeader_V2
        {
            unsigned char aSignature[4]; //YSTB
            unsigned int uiVersion; //224 - 300
            unsigned int uiCodeSegSize;
            unsigned int uiResSegSize;
            unsigned int uiResOffset;
            unsigned int uiReserved0;
            unsigned int uiReserved1;
            unsigned int uiReserved2;
        };

        #pragma pack(1)
        struct Instruction_V2
        {
            unsigned char ucOP;
            unsigned char ucArgs;
            unsigned int ucLine;
        };
        #pragma pack()

        struct ResEntry_V2
        {
            unsigned short usUn0;
            unsigned short usUn1;
            unsigned int uiResSize;
            unsigned int uiResRVA;
        };

        struct ResInfo_V2
        {
            unsigned char ucType;
            unsigned short usSize;
            //pData[usSize];
        };

        /*
          Res
          unsigned char ucType
          unsigned short usResLen
          unsigned char* pData[usResLen]
          
          ucType
          0x4D -> push string
          0x42 -> push int8
          0x52 -> changesign
          0x57 -> push int16
        */

        //0x8  08 00 ???????? 位于代码段结束位置

        /*
        * 0x19 读取一些es.开头的字符串 es.VoiceSetTask es.BGM
          1904     -> OP
          1C000000 -> OrgCodeTextLineNumber?
          0000
          0300
          0B000000 ->len: es.BGM
          60010000 ->rva:
          1100
          0300
          0A000000 ->len: BGM07
          6B010000 ->rva:
          0200
          0100
          04000000 ->len: int8 0x00
          75010000 ->rva:
          0300
          0100
          07000000 ->len: int8 0x01
          79010000 ->rva:
        */

        //0x18,0x1A,0x1E,0x23,0x38,0x4D,0x4F,0x50
        
        //0x54 读取对话字符串
        /*
          54        op
          01        len = 0x01*0C + 6 / (if op == 0x38，len = 0xA)
          BA000000  un0
          00000000  un1
          26000000  lenStr
          05140000  offStr
        */

    }
}
