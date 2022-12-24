#include "YSTB.h"
#include <fstream>
#include <typeinfo>
#include "Tools.h"
#include "FileStruct.h"
using namespace ORG_Struct;

void YSTB::XorScript(std::string strYSTB, unsigned char* aXorKey)
{
	char* pSeg = nullptr;
	char* pYSTB = nullptr;
	unsigned int size = 0;
	unsigned int magic = 0;
	unsigned int version = 0;


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
			size = Tools::GetFileSize(iYSTB);
			pYSTB = new char[size];
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
