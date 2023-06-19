#include "../../lib/YurisStaticLibrary/YSCFG.h"

using namespace YurisLibrary;


int wmain(int argc, wchar_t* argv[])
{
	if (argc > 1)
	{
		YSCFG::YSCFG_V5 yscfg(argv[1]);
		yscfg.ToJson(L"yscfg.json");
	}

	if (argc == 1)
	{
		YSCFG::YSCFG_V5 yscfg(L"yscfg.ybn");
		yscfg.ToJson(L"yscfg.json");
	}
}