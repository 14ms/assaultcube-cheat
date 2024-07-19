#include "pch.h"

#include "Module.h"

#include "src/cheat/Console.h"

Module::Module(const std::string_view& name, const KeyBind& keyBind)
	: m_Name{ name }, m_KeyBind{ keyBind }
{
}

void Module::SetEnabled(bool state)
{
	if (m_IsEnabled == state)
	{
		return;
	}

	if (state)
	{
		OnEnable();
	}
	else
	{
		OnDisable();
	}

	m_IsEnabled = state;
	Console::PrintModules();
}

void Module::OnUpdate()
{
}

void Module::OnEnable()
{
}

void Module::OnDisable()
{
}

const std::string_view& Module::GetName() const
{
	return m_Name;
}

const KeyBind& Module::GetBind() const
{
	return m_KeyBind;
}

bool Module::IsEnabled() const
{
	return m_IsEnabled;
}

bool Module::IsEnabledByDefault() const
{
	return m_IsEnabledByDefault;
}
