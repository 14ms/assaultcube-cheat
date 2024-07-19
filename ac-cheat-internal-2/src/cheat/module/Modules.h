#pragma once

#include "movement/Speed.h"
#include "movement/Fly.h"
#include "movement/AirJump.h"

#include "visual/FOV.h"
#include "visual/ESP.h"

#include "combat/NoDelay.h"
#include "combat/InfAmmo.h"
#include "combat/Trigger.h"
#include "combat/GodMode.h"
#include "combat/AimBot.h"

namespace Modules
{
	inline std::vector<Module*> modules;

	void AddModule(Module& mod);
	void InitModules();

	void EnableModulesByDefault();
	void DisableModules();
	void UpdateModules();
}