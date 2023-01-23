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
            char aSignature[4]; //YSTB
            int iVersion; //300 - 
            int iInstructionCount;
            int iInstructionsSize; //iInstructionCount * 4
            int iAttributeDescriptorsSize;
            int iAttributeValuesSize;
            int iLineNumbersSize;
            int iPadding;
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
        *   CodeSegment
        *   ResSegment
        * }
        */
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
        //op -> 0x19 0x18 0x1A 0x1E 0x23 0x50 0x54 
        /*	PushString
        *	54			op
            01			len = 0x01*0C + 6 / (if op == 0x38£¬len = 0xA)
            BA000000	un0
            00000000	un1
            26000000	lenStr
            05140000	offStr
        */
    }
}
