#include <iostream>

#include "..\YurisStaticLibrary\YPF.h"


int main()
{
	YPF ypf(L"ysbin.ypf");
	ypf.DecodeFile_WZ();
}