#include "pch.h"

#include "GodMode.h"

GodMode::GodMode() : Module("GodMode", 'P')
{
}

void GodMode::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		plr->m_Health = 999;
	}
}

void GodMode::OnDisable()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		plr->m_Health = 100;
	}
}
