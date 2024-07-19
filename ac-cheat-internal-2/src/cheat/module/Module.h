#pragma once

#include "src/cheat/Cheat.h"
#include "src/input/KeyBind.h"
#include "src/utils/Singleton.h"

class Module
{
protected:
	static inline Game& s_Game = Cheat::game;

private:
	const std::string_view m_Name;
	KeyBind m_KeyBind;

	bool m_IsEnabled = false;
protected:
	bool m_IsEnabledByDefault = false;

public:
	Module(const std::string_view& name, const KeyBind& keyBind = 0);

	void SetEnabled(bool state);

	virtual void OnUpdate();

	virtual void OnEnable();
	virtual void OnDisable();

	const std::string_view& GetName() const;
	const KeyBind& GetBind() const;

	bool IsEnabled() const;
	bool IsEnabledByDefault() const;
};