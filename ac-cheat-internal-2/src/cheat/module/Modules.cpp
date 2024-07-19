#include "pch.h"

#include "Modules.h"

#include "src/cheat/Console.h"

void Modules::AddModule(Module& mod)
{
	modules.push_back(&mod);
}

void Modules::InitModules()
{
	AddModule(Speed::Instance());
	AddModule(Fly::Instance());
	AddModule(FOV::Instance());
	AddModule(NoDelay::Instance());
	AddModule(InfAmmo::Instance());
	AddModule(AirJump::Instance());
	AddModule(Trigger::Instance());
	AddModule(GodMode::Instance());
	AddModule(AimBot::Instance());
	AddModule(ESP::Instance());
}

void Modules::EnableModulesByDefault()
{
	for (Module* mod : modules)
	{
		if (mod->IsEnabledByDefault())
		{
			mod->SetEnabled(true);
		}
	}
}

void Modules::DisableModules()
{
	for (Module* mod : modules)
	{
		mod->SetEnabled(false);
	}
}

void Modules::UpdateModules()
{
	for (Module* mod : modules)
	{
		if (mod->IsEnabled())
		{
			mod->OnUpdate();
		}
	}
}