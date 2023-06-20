#include <iostream>

#include "../../lib/Rxx/File.h"
#include "../../lib/Rxx/Console.h"
#include "../../lib/YurisStaticLibrary/YSTB.h"


using namespace Rut::FileX;
using namespace Rut::ConsoleX;
using namespace YurisLibrary;


int main(int argc, char* argv[])
{
	try
	{
		std::ifstream key_text = OpenFileANSIStream(L"Key.txt");
		uint32_t key = 0;
		key_text >> std::hex >> key;

		std::vector<std::wstring> ybn_file_list;
		GetAllFileNameW(L"ysbin/", ybn_file_list);

		YSTB::YSTB_Coder coder(key);
		for (auto& ybn_name : ybn_file_list)
		{
			if (coder.Xor(L"ysbin/" + ybn_name, L"ysbin_dec/" + ybn_name))
			{
				PutConsoleW(L"Xor: -> %s -> key:0x%X\n", ybn_name.c_str(), key);
			}
		}
		system("pause");
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		system("pause");
	}
}