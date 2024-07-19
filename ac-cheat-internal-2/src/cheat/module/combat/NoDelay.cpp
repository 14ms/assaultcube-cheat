#include "pch.h"

#include "NoDelay.h"

NoDelay::NoDelay() : Module("NoDelay")
{
}

void NoDelay::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		Item* curItem = plr->m_CurrentItem;

		if (curItem)
		{
			*curItem->m_ShootDelay = 0;
		}
	}
}
