#pragma once

#include "../Module.h"

class InfAmmo : public Module, public Singleton<InfAmmo>
{
	friend Singleton<InfAmmo>;

private:
	InfAmmo();

public:
	void OnUpdate() override;
	void OnDisable() override;
};