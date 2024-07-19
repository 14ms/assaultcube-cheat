#pragma once

#include "../Module.h"

class FOV : public Module, public Singleton<FOV>
{
	friend Singleton<FOV>;

private:
	FOV();

	float m_OldFov = 90;

public:
	void OnUpdate() override;
	void OnEnable() override;
	void OnDisable() override;
};