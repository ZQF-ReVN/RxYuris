#pragma once

namespace YPF_Struct
{
	//frome crass/cui/YU-RIS/YU-RIS.cpp
	struct YPFHeader_V2
	{
		char aSignature[4];             // "YPF"
		unsigned int uiVersion;         // version > 200
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
		unsigned int uiNameCrc;
		unsigned char szEncName; //NameSizeTable[0xFF-szName]
		char aEncName[256];
		unsigned char ucFileType;
		bool isCompFlag;
		unsigned int uiDecompSize;
		unsigned int uiCompSize;
		unsigned long long ullDataOffset;
		unsigned int uiDataCrc;// MurmurHash
	};
	#pragma pack()
}