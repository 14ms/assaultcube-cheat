#pragma once

#include "../Module.h"

class ESP : public Module, public Singleton<ESP>
{
	friend Singleton<ESP>;

private:
	ESP();

public:
	void OnUpdate() override;
	void OnDisable() override;
};