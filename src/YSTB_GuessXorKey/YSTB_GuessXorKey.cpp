#include <iostream>

#include "../../lib/YurisStaticLibrary/YSTB.h"

#include "../../lib/Rxx/File.h"

using namespace Rut::FileX;
using namespace YurisLibrary;


int wmain(int argc, wchar_t* argv[])
{
	if (argc <= 1)
	{
		std::cout
			<< "YSTB_GuessXorKey:\n"
			<< "\tChoose the largest ystb file as possible\n"
			<< "Example\n"
			<< "\YSTB_GuessXorKey.exe yst00004.ybn\n\n";

		system("pasue");
		return 0;
	}

	try
	{
		YSTB::YSTB_Coder coder(0);
		uint32_t key = coder.GetXorKey(argv[1]);
		std::ofstream ofs_text = CreateFileANSIStream(L"Key.txt");
		ofs_text << "0x" << std::hex << (uint32_t*)key << std::endl;
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		system("pause");
	}

}