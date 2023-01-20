#pragma once

namespace YPF_Struct
{
	/*
	* YPF_File
	* - YPFHeader
	* - YPFEntry[YPFHeader->uiIndexEntryCount]
	* - Data
	*/

	//frome crass/cui/YU-RIS/YU-RIS.cpp
	struct YPFHeader_V2
	{
		char aSignature[4];              // "YPF"
		unsigned int uiVersion;          // version > 200
		unsigned int uiIndexEntryCount;
		unsigned int uiIndexBlockSize;
		unsigned int uiReserved0;
		unsigned int uiReserved1;
		unsigned int uiReserved2;
		unsigned int uiReserved3;
	};

	#pragma pack(1)
	struct YPFEntry_V5
	{
		unsigned int uiEncNameCrc;
		unsigned char szEncName;          // NameSizeTable[0xFF-szName]
		char aEncName[256];
		unsigned char ucFileType;
		unsigned char isCompFlag;
		unsigned int uiDecompSize;
		unsigned int uiCompSize;
		unsigned long long ullDataOffset;
		unsigned int uiDataCrc;           // MurmurHash
	};
	#pragma pack()
}