#pragma once

#include "../Module.h"

class GodMode : public Module, public Singleton<GodMode>
{
	friend Singleton<GodMode>;

private:
	GodMode();

public:
	void OnUpdate() override;
	void OnDisable() override;
};