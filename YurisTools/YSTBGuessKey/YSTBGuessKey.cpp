#include <iostream>

#include "..\YurisStaticLibrary\YSTB.h"

void GuessKey()
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
	GuessKey();
}