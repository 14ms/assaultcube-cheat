#pragma once

#include "../Module.h"

class AirJump : public Module, public Singleton<AirJump>
{
	friend Singleton<AirJump>;

private:
	AirJump();

public:
	void OnUpdate() override;
	void OnDisable() override;
};