#include "pch.h"

#include "Cheat.h"

#include "src/cheat/Console.h"
#include "src/cheat/module/Modules.h"

bool Cheat::Start()
{
	if (!Console::Open() || !game.Init())
	{
		return false;
	}

	Console::PrintTitle();

	Modules::InitModules();
	Modules::EnableModulesByDefault();

	return true;
}

void Cheat::Stop()
{
	if (Console::isAttached)
	{
		Console::Free();
	}

	Modules::DisableModules();
}