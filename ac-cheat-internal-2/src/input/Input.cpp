#include "pch.h"

#include "Input.h"

#include "src/cheat/module/Modules.h"

//#define DEBUG

static void HandleKeyBinds(uint8_t key, bool isDown)
{
	if (!isDown)
	{
		return;
	}

	if (key == VK_INSERT)
	{
		Cheat::isStopping = true;
		return;
	}

	for (Module* module : Modules::modules)
	{
		Module& mod = *module;

		if (mod.GetBind().HasKey() && mod.GetBind().GetKey() == key)
		{
			mod.SetEnabled(!mod.IsEnabled());
		}
	}
}

static bool IsKeyPrintable(uint8_t key)
{
	return key >= 32 && key <= 126;
}

static void PrintKey(uint8_t key)
{
	if (IsKeyPrintable(key))
	{
		std::cout << key;
	}
	else
	{
		std::cout << '<' << (int)key << '>';
	}
}

void InputSystem::OnKeyboard(uint8_t key, bool isDown)
{
#ifdef DEBUG
	std::cout << "[INFO] InputSystem::OnKeyboard() "; PrintKey(key);
	std::cout << ' ' << isDown << '\n';
#endif

	HandleKeyBinds(key, isDown);
}

void InputSystem::OnMouse(MouseButton button, bool isDown)
{
#ifdef DEBUG
	std::cout << "[INFO] InputSystem::OnMouse() " << (int)button << ' ' << isDown << '\n';
#endif
}

void InputSystem::UpdateKeyState(uint8_t key, bool isDown)
{
	if (isDown != m_KeyStates[key])
	{
		m_KeyStates[key] = isDown;
		OnKeyboard(key, isDown);
	}
}

void InputSystem::UpdateKeyStates()
{
	if (Cheat::isStopping)
	{
		return;
	}

	for (uint8_t key : m_KeysToUpdate)
	{
		UpdateKeyState((uint8_t)key, GetKeyState(key) & 0x8000);
	}
}