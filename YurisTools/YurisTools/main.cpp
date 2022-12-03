#include "YSTList.h"
#include "YSTB.h"

void MakeDir()
{
	char flag = 0;
	std::cout << "input m make directary and rename .ybn to real file name.\n";
	std::cout << "input r restore file and file name from directory.\n";
	std::cout << "input c count how much text is in file.\n\n";
	std::cout << "input:";
	std::cin >> flag;
	std::cout << std::endl;

	YSTList yst(L"yst_list.ybn");
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
}

int main(int argc, char* argv[])
{

}