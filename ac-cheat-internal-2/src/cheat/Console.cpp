#include "pch.h"

#include "Console.h"

#include "module/Modules.h"

bool Console::Open()
{
	BOOL result = AllocConsole();

	if (!result)
	{
		return false;
	}

	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD consoleMode;
	GetConsoleMode(handleOut, &consoleMode);
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
	consoleMode |= CURSOR_SHOWING;
	SetConsoleMode(handleOut, consoleMode);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handleOut, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handleOut, &cursorInfo);

	SetConsoleTitleA("ac cheat");

	FILE* temp;
	freopen_s(&temp, "CONIN$", "r", stdin);
	freopen_s(&temp, "CONOUT$", "w", stderr);
	freopen_s(&temp, "CONOUT$", "w", stdout);

	isAttached = true;
	return true;
}

void Console::Free()
{
	if (!isAttached)
	{
		return;
	}

	HWND winId = GetConsoleWindow();

	if (winId)
	{
		ShowWindow(winId, 0);
	}

	FreeConsole();
}

#define COLOR_0 "\x1b[38;5;76m"
#define COLOR_1 "\x1b[38;5;77m"
#define COLOR_2 "\x1b[38;5;78m"
#define COLOR_3 "\x1b[38;5;79m"
#define COLOR_4 "\x1b[38;5;65m"

void Console::PrintTitle()
{
	std::cout << COLOR_3 R"RAW(
                             .__                   __   
      _____    ____     ____ |  |__   ____ _____ _/  |_ 
      \__  \ _/ ___\  _/ ___\|  |  \_/ __ \\__  \\   __\
       / __ \\  \___  \  \___|   Y  \  ___/ / __ \|  |  
      (____  /\___  >  \___  >___|  /\___  >____  /__|  
           \/     \/       \/     \/     \/     \/      )RAW";
}

void Console::Print(const Module& module)
{
	char modKey = module.GetBind().HasKey() ? module.GetBind().GetKey() : '-';
	const char* modState = module.IsEnabled() ? "on " : "off";

	std::cout << COLOR_2 "       ";
	std::cout << std::left << std::setw(8) << module.GetName();
	std::cout << " [ " COLOR_4 << modKey << COLOR_2 " ]";
	std::cout << " ( " COLOR_4 << modState << COLOR_2 " )\n";
}

static void SetCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Console::PrintModules()
{
	SetCursorPosition(0, 10);

	for (Module* mod : Modules::modules)
	{
		Print(*mod);
	}
}