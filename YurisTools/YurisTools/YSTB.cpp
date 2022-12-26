#include "YSTB.h"
#include <fstream>
#include "..\Tools\FileX.h"
#include "FileStruct.h"
using namespace ORG_Struct;

void YSTB::TextDump_V2(std::string strYSTB)
{
	std::ifstream iYSTB(strYSTB, std::ios::binary);
	std::ofstream oText(strYSTB + ".txt");
	if (iYSTB.is_open() && oText.is_open())
	{
		char* pYSTB = nullptr;
		char* pCodeSeg = nullptr;
		char* pResSeg = nullptr;
		std::streamsize szYSTB = 0;
		YSTBHeader_V2* header = nullptr;

		//Read YSTB File To Buffer
		szYSTB = FileX::GetFileSize(iYSTB);
		pYSTB = new char[szYSTB];
		if (pYSTB)
		{
			iYSTB.read(pYSTB, szYSTB);
		}
		else
		{
			iYSTB.close();
			return;
		}

		//Init Info
		header = reinterpret_cast<YSTBHeader_V2*>(pYSTB);
		pCodeSeg = pYSTB + sizeof(YSTBHeader_V2);
		pResSeg = pYSTB + header->iResOffset;

		//Analyzing VM
		//op -> 0x19 0x18 0x1A 0x1E 0x23 0x50 0x54 
		/*	PushString
		*	54			op
			01			len = 0x01*0C + 6 / (if op == 0x38£¬len = 0xA)
			BA000000	un0
			00000000	un1
			26000000	lenStr
			05140000	offStr
		*/
		unsigned int textLen = 0;
		unsigned int textOff = 0;
		char buffer[0xFF] = { 0 };
		for (int iteCodeSize = 0; iteCodeSize <= header->iCodeSegSize;)
		{
			switch (pCodeSeg[iteCodeSize])
			{
			case 0x19:
				break;

			case 0x18:
				break;

			case 0x1A:
				break;

			case 0x1E:
				break;

			case 0x23:
				break;

			case 0x38:
				iteCodeSize += 0xA;
				continue;
				break;

			case 0x50:
				break;

			case 0x54:
				if (pCodeSeg[iteCodeSize + 1] == 1)
				{
					textLen = *reinterpret_cast<unsigned int*>(pCodeSeg + iteCodeSize + 10);
					textOff = *reinterpret_cast<unsigned int*>(pCodeSeg + iteCodeSize + 14);
					memcpy(buffer, pResSeg + textOff, textLen);
					buffer[textLen + 1] = '\0';

					oText << textOff << '\n';
					oText << buffer << "\n\n";

				}
				break;
			}

			//Size Of Code Block
			iteCodeSize += pCodeSeg[iteCodeSize + 1] * 0xC + 6;
		}


		delete[] pYSTB;
		pYSTB = nullptr;
		pCodeSeg = nullptr;
		pResSeg = nullptr;
		iYSTB.close();
		oText.flush();
		oText.close();
	}
}

void YSTB::XorScript(std::string strYSTB, unsigned char* aXorKey)
{
	char* pSeg = nullptr;
	char* pYSTB = nullptr;
	unsigned int magic = 0;
	unsigned int version = 0;
	std::streamsize size = 0;


	std::ifstream iYSTB(strYSTB, std::ios::binary);
	if (iYSTB.is_open())
	{
		//Check is YSTB file
		iYSTB.read(reinterpret_cast<char*>(&magic), 4);
		iYSTB.read(reinterpret_cast<char*>(&version), 4);
		iYSTB.seekg(0, std::ios::beg);
		if (magic == 0x42545359)
		{
			//Read Buffer
			size = FileX::GetFileSize(iYSTB);
			pYSTB = new char[static_cast<size_t>(size)];
			if (!pYSTB)
			{
				return;
			}
			iYSTB.read(pYSTB, size);

			//Skip File Header
			pSeg = pYSTB + 0x20;

			//Dec
			if (version > 200 && version < 300)
			{
				YSTBHeader_V2* pHeader = reinterpret_cast<YSTBHeader_V2*>(pYSTB);
				for (size_t iteData = 0; iteData < static_cast<size_t>(pHeader->iCodeSegSize); iteData++)
				{
					pSeg[iteData] ^= aXorKey[iteData & 3];
				}

				pSeg += pHeader->iCodeSegSize;

				for (size_t iteData = 0; iteData < static_cast<size_t>(pHeader->iResSegSize); iteData++)
				{
					pSeg[iteData] ^= aXorKey[iteData & 3];
				}
			}
			else
			{
				size_t szSegment = 0;
				for (size_t iteSegments = 0; iteSegments < 4; iteSegments++)
				{
					szSegment = *(reinterpret_cast<unsigned int*>(pYSTB) + 3 + iteSegments);
					for (size_t iteData = 0; iteData < szSegment; iteData++)
					{
						pSeg[iteData] ^= aXorKey[iteData & 3];
					}
					pSeg += szSegment;
				}
			}
			pSeg = nullptr;

			//Save Buffer To New File
			std::ofstream oYSTB(strYSTB + ".dec", std::ios::binary);
			if (oYSTB.is_open())
			{
				oYSTB.write(pYSTB, size);
				oYSTB.flush();
				oYSTB.close();
			}

			delete[] pYSTB;
			pYSTB = nullptr;
		}

		iYSTB.close();
	}
}

void YSTB::GuessXorKey(std::string strYSTB, unsigned char* aXorKey)
{
	unsigned int key = 0;
	unsigned int version = 0;

	std::ifstream iYSTB(strYSTB, std::ios::binary);
	if (iYSTB.is_open())
	{
		iYSTB.seekg(4);
		iYSTB.read(reinterpret_cast<char*>(&version), 4);
		iYSTB.seekg(0);

		//Check Version
		if (version > 200 && version < 300)
		{
			YSTBHeader_V2 header = { 0 };
			iYSTB.read(reinterpret_cast<char*>(&header), sizeof(YSTBHeader_V2));
			if ((header.iCodeSegSize + header.iResSegSize) < 0x10)
			{
				*reinterpret_cast<unsigned int*>(aXorKey) = 0;
			}
			else
			{
				iYSTB.seekg(0x2C);
				iYSTB.read(reinterpret_cast<char*>(&key), 4);
			}
		}
		else
		{
			//Init Header
			YSTBHeader_V5 header = { 0 };
			iYSTB.read(reinterpret_cast<char*>(&header), sizeof(YSTBHeader_V5));

			if (header.iAttributeValuesSize == 0)
			{
				*reinterpret_cast<unsigned int*>(aXorKey) = 0;
			}
			else
			{
				//Read The First AttributeDescriptor iOffset == 0
				iYSTB.seekg(static_cast<std::streampos>(header.iInstructionsSize + sizeof(YSTBHeader_V5) + 0x8));
				iYSTB.read(reinterpret_cast<char*>(&key), 4);
			}
		}
		*reinterpret_cast<unsigned int*>(aXorKey) = key;

		iYSTB.close();
	}
}
