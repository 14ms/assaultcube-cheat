#include "pch.h"

#include "InfAmmo.h"

InfAmmo::InfAmmo() : Module("InfAmmo")
{
}

void InfAmmo::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		Item* curItem = plr->m_CurrentItem;

		if (curItem)
		{
			*curItem->m_ClipAmmo = 999;
		}
	}
}

void InfAmmo::OnDisable()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		Item* curItem = plr->m_CurrentItem;

		if (curItem)
		{
			*curItem->m_ClipAmmo = 0;
		}
	}
}