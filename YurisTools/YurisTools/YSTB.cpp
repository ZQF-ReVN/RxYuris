#include "YSTB.h"

void YSTB::XorScript(std::string strYSTB, unsigned char* aXorKey)
{
	unsigned int magicFlag = 0;
	unsigned int ystbSize = 0;

	std::ifstream iScript(strYSTB, std::ios::binary);
	if (iScript.is_open())
	{
		//Check is YSTB file
		iScript.read((char*)&magicFlag, 4);
		iScript.seekg(0, std::ios::beg);
		if (magicFlag == 0x42545359)
		{
			//Read Buffer
			ystbSize = Tools::GetFileSize(iScript);
			char* pYstb = new char[ystbSize];
			if (!pYstb)
			{
				return;
			}
			iScript.read(pYstb, ystbSize);

			//Skip File Header
			char* pDec = pYstb + 0x20;

			//Dec
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
		}

		iScript.close();
	}
}