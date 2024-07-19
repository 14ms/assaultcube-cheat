#pragma once

#include "../Module.h"

class Fly : public Module, public Singleton<Fly>
{
	friend Singleton<Fly>;

private:
	Fly();

public:
	void OnUpdate() override;
	void OnDisable() override;
};