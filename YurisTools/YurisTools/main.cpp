#include "YSTList.h"
#include "YSTB.h"

void MakeDir()
{
	auto fileName = LR"(yst_list.ybn)";
	char flag = 0;

	std::cout 
		<< "input m make directary and rename .ybn to real file name.\n"
		<< "input r restore file and file name from directory.\n"
		<< "input c count how much text is in file.\n\n"
		<< "input:";
	std::cin >> flag;
	std::cout << std::endl;

	YSTList yst(fileName);
	if (flag == 'm')
	{
		yst.MakeDir();
		std::cout << "Save As ysbin_MakeDir\n";
	}

	if (flag == 'r')
	{
		yst.RestoreDir();
		std::cout << "Save As ysbin_RestoreDir\n";
	}

	if (flag == 'c')
	{
		yst.TextCount();
		std::cout << "Save As TextCout.txt\n";
	}

	system("pause");
}

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

void GuassKey()
{
	std::string fileName;
	unsigned char xorKey[4] = { 0 };

	std::cout << "Input File Name:";
	std::cin >> fileName;

	YSTB::GuessXorKey(fileName, xorKey);

	std::cout << "0x" << std::hex << *(int*)xorKey << std::endl;
}

int main(int argc, char* argv[])
{
	//GuassKey();
	XorFile(argc, argv);
}