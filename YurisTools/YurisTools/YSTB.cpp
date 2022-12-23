#include "YSTB.h"
#include <fstream>
#include "Tools.h"
#include "FileStruct.h"
using namespace ORG_Struct;

void YSTB::XorScript(std::string strYSTB, unsigned char* aXorKey)
{
	char* pDec = nullptr;
	char* pYstb = nullptr;
	unsigned int version = 0;
	unsigned int ystbSize = 0;
	unsigned int magicFlag = 0;


	std::ifstream iScript(strYSTB, std::ios::binary);
	if (iScript.is_open())
	{
		//Check is YSTB file
		iScript.read((char*)&magicFlag, 4);
		iScript.read((char*)&version, 4);
		iScript.seekg(0, std::ios::beg);
		if (magicFlag == 0x42545359)
		{
			//Read Buffer
			ystbSize = Tools::GetFileSize(iScript);
			pYstb = new char[ystbSize];
			if (!pYstb)
			{
				return;
			}
			iScript.read(pYstb, ystbSize);

			//Skip File Header
			pDec = pYstb + 0x20;

			//Dec
			if (version > 200 && version < 300)
			{
				YSTBHeader_V2* header = (YSTBHeader_V2*)pYstb;
				for (size_t iteSegment = 0; iteSegment < header->iCodeSegSize; iteSegment++)
				{
					pDec[iteSegment] ^= aXorKey[iteSegment & 3];
				}

				pDec += header->iCodeSegSize;

				for (size_t iteSegment = 0; iteSegment < header->iResSegSize; iteSegment++)
				{
					pDec[iteSegment] ^= aXorKey[iteSegment & 3];
				}
			}
			else
			{
				size_t szSegment = 0;
				for (size_t Segments = 0; Segments < 4; Segments++)
				{
					szSegment = *((unsigned int*)pYstb + 3 + Segments);
					for (size_t iteSegment = 0; iteSegment < szSegment; iteSegment++)
					{
						pDec[iteSegment] ^= aXorKey[iteSegment & 3];
					}
					pDec += szSegment;
				}
			}
			pDec = nullptr;

			//Save Buffer To New File
			std::ofstream oScript(strYSTB + ".dec", std::ios::binary);
			if (oScript.is_open())
			{
				oScript.write(pYstb, ystbSize);
				oScript.flush();
				oScript.close();
			}

			delete[] pYstb;
			pYstb = nullptr;
		}

		iScript.close();
	}
}

void YSTB::GuessXorKey(std::string strYSTB, unsigned char* aXorKey)
{
	int version = 0;
	unsigned int key = 0;
	std::ifstream iScript(strYSTB, std::ios::binary);
	if (iScript.is_open())
	{
		iScript.seekg(4);
		iScript.read((char*)&version, 4);
		iScript.seekg(0);

		//Check Version
		if (version > 200 && version < 300)
		{
			YSTBHeader_V2 header = { 0 };
			iScript.read((char*)&header, sizeof(YSTBHeader_V2));
			if ((header.iCodeSegSize + header.iResSegSize) < 0x10)
			{
				*(unsigned int*)aXorKey = 0;
			}
			else
			{
				iScript.seekg(0x2C);
				iScript.read((char*)&key, 4);
			}
		}
		else
		{
			//Init Header
			YSTBHeader_V5 header = { 0 };
			iScript.read((char*)&header, sizeof(YSTBHeader_V5));

			if (header.iAttributeValuesSize == 0)
			{
				*(unsigned int*)aXorKey = 0;
			}
			else
			{
				size_t pos = header.iInstructionsSize + sizeof(YSTBHeader_V5) + 0x8;

				//Read The First AttributeDescriptor iOffset == 0
				iScript.seekg(pos);
				iScript.read((char*)&key, 4);
			}
		}
		*(unsigned int*)aXorKey = key;

		iScript.close();
	}
}
