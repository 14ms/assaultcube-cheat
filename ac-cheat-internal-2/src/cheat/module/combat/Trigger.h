#pragma once

#include "../Module.h"

class Trigger : public Module, public Singleton<Trigger>
{
	friend Singleton<Trigger>;

private:
	Trigger();

	bool m_BlockShooting = false;

public:
	void OnUpdate() override;
	void OnEnable() override;
	void OnDisable() override;
};