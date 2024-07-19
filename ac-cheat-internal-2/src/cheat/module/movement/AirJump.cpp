#include "pch.h"

#include "AirJump.h"

AirJump::AirJump() : Module("AirJump", 'L')
{
}

void AirJump::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		plr->m_isOnGround = true;
	}
}

void AirJump::OnDisable()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		plr->m_isOnGround = false;
	}
}