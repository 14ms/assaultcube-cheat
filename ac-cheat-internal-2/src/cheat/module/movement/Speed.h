#pragma once

#include "../Module.h"

class Speed : public Module, public Singleton<Speed>
{
	friend Singleton<Speed>;

private:
	Speed();

public:
	void OnUpdate() override;
	void OnDisable() override;
};