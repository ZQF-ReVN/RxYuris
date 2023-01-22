#include <iostream>

#include "..\YurisStaticLibrary\YSTB.h"


void XorFile(int argc, char* argv[])
{
	unsigned char xorKey[4] = { 0 };
	if (argc > 1)
	{
		if (sscanf_s(argv[2], "0x%x", (unsigned int*)(&xorKey)))
		{
			YSTB::XorScript(argv[1], xorKey);
		}
	}
	else
	{
		std::cout
			<< "YurisTools.exe [FileName] [XorKey]"
			<< "YurisTools.exe yst00000.ybn 0xABCFADAE"
			<< std::endl;
	}
}

int main(int argc, char* argv[])
{
	XorFile(argc, argv);
}