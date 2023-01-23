#include <iostream>

#include "..\YurisStaticLibrary\YSTB.h"

using namespace YurisStaticLibrary;



void TextEditor()
{
	char flag = 0;
	std::string fileName;
	unsigned int exCodePage = 932;
	unsigned int inCodePage = 936;

	std::cout
		<< "input e Extract text.\n"
		<< "input i Insert text.\n"
		<< "input c Change code page.\n\n"
		<< "Current CodePage\n"
		<< "Extract CodePage:" << exCodePage << '\n'
		<< "Insert  CodePage:" << inCodePage << "\n\n"
		<< "input:";

	while (true)
	{
		std::cout << "input:";
		std::cin >> flag;

		switch (flag)
		{
		case 'e':
			std::cout << "input filename:";
			std::cin >> fileName;
			YSTB::TextDump_V2(fileName, exCodePage);
			break;

		case 'i':
			std::cout << "input filename:";
			std::cin >> fileName;
			YSTB::TextInset_V2(fileName, inCodePage);
			break;

		case 'c':
			std::cout << "Extract CodePage:";
			std::cin >> exCodePage;
			std::cout << "Insert CodePage:";
			std::cin >> inCodePage;

			std::cout << "CodePage has changed" << "\n\n";
			std::cout
				<< "Current CodePage\n"
				<< "Extract CodePage:" << exCodePage << '\n'
				<< "Insert  CodePage:" << inCodePage << std::endl;
		}

		std::cout << std::endl;
	}
}


int main()
{
	TextEditor();
}