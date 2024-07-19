#pragma once

#include "../Module.h"

class NoDelay : public Module, public Singleton<NoDelay>
{
	friend Singleton<NoDelay>;

private:
	NoDelay();

public:
	void OnUpdate() override;
};