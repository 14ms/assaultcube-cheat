#pragma once

#include "src/utils/Singleton.h"

class InputSystem : public Singleton<InputSystem>
{
	friend class Singleton;

public:
	enum MouseButton : uint8_t
	{
		RIGHT,
		LEFT,
		MIDDLE
	};

	void OnKeyboard(uint8_t key, bool isDown);
	void OnMouse(MouseButton button, bool isDown);

	void UpdateKeyState(uint8_t key, bool isDown);
	void UpdateKeyStates();

private:
	InputSystem()
	{
	}

	uint8_t m_KeysToUpdate[26 + 1] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		VK_INSERT
	};
	bool m_KeyStates[256] = {};
};