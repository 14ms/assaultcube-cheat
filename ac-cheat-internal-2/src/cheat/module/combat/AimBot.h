#pragma once

#include "../Module.h"

class AimBot : public Module, public Singleton<AimBot>
{
	friend Singleton<AimBot>;

private:
	AimBot();

public:
	void OnUpdate() override;
};