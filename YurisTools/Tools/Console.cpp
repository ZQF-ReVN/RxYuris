#include "Console.h"


DWORD WINAPI SetConsoleTop(LPVOID lpParameter)
{
	HWND hConsole = 0;
	WCHAR consoleTitle[256] = { 0 };

	while (true)
	{
		GetConsoleTitleW(consoleTitle, 256);
		hConsole = FindWindowW(NULL, (LPWSTR)consoleTitle);
		if (hConsole != NULL)
		{
			SetWindowPos(hConsole, HWND_TOPMOST, NULL, NULL, NULL, NULL, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
			break;
		}
	}

	return 0;
}

FILE* Console::SetConsole(LPCWSTR lpTitle)
{
	DWORD mode = 0;
	FILE* fpStreamConsole = 0;

	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen_s(&fpStreamConsole, "CONIN$", "r+t", stdin);
	freopen_s(&fpStreamConsole, "CONOUT$", "w+t", stdout);

	SetConsoleTitleW(lpTitle);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SetConsoleTop, NULL, NULL, NULL);

	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode & ~ENABLE_QUICK_EDIT_MODE);

	//system("chcp 65001");
	//setlocale(LC_ALL, "chs");
	std::locale::global(std::locale(""));

	return fpStreamConsole;
}