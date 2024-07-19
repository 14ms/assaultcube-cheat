#include "pch.h"

#include "KeyBind.h"

KeyBind::KeyBind(uint8_t keyCode) : m_KeyCode{ keyCode }
{
}

KeyBind::KeyBind() : m_KeyCode{ 0 }
{
}

uint8_t KeyBind::GetKey() const
{
	return m_KeyCode;
}

bool KeyBind::HasKey() const
{
	return m_KeyCode;
}

void KeyBind::SetKey(uint8_t key)
{
	m_KeyCode = key;
}