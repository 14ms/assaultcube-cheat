#pragma once

#include "Input.h"

class KeyBind
{
public:
	KeyBind(uint8_t keyCode);
	KeyBind();

	uint8_t GetKey() const;
	bool HasKey() const;
	void SetKey(uint8_t key);

private:
	uint8_t m_KeyCode;
};