#include <iostream>

#include "..\YurisTools\YSTList.h"


void YSTListTools()
{
	auto fileName = LR"(yst_list.ybn)";
	char flag = 0;

	std::cout
		<< "input m make directary and rename .ybn to real file name.\n"
		<< "input r restore file and file name from directory.\n"
		<< "input i exporting information to text.\n\n"
		<< "input:";
	std::cin >> flag;
	std::cout << std::endl;

	YSTList yst(fileName);
	if (flag == 'm')
	{
		yst.MakeDirStructure();
		std::cout << "Save As ysbin_MakeDir\n";
	}

	//if (flag == 'r')
	//{
	//	yst.RestoreDir();
	//	std::cout << "Save As ysbin_RestoreDir\n";
	//}

	if (flag == 'i')
	{
		yst.PrintIndexToFile();
		std::cout << "Save As YSTList_Info.txt\n";
	}

	system("pause");
}

int main()
{
	YSTListTools();
}