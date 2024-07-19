#include "pch.h"

#include "Trigger.h"

Trigger::Trigger() : Module("Trigger", 'K')
{
}

void Trigger::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (!plr)
	{
		return;
	}

	Player* lookingPlr = s_Game.GetLookingEntity();

	if (lookingPlr)
	{
		if (!lookingPlr->IsAlive() || plr->IsTeamate(lookingPlr))
		{
			return;
		}

		m_BlockShooting = true;
		plr->m_IsShooting = true;
	}
	else if (m_BlockShooting)
	{
		m_BlockShooting = false;
		plr->m_IsShooting = false;
	}
}

void Trigger::OnEnable()
{
}

void Trigger::OnDisable()
{
}
