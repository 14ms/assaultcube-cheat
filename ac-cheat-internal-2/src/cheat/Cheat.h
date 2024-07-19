#pragma once

#include "src/sdk/Game.h"

namespace Cheat
{
	inline Game game;
	inline bool isStopping = false;

	bool Start();
	void Stop();
};