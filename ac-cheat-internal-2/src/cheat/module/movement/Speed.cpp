#include "pch.h"

#include "Speed.h"

Speed::Speed() : Module("Speed", 'Z')
{
	//m_IsEnabledByDefault = true;
}

void Speed::OnUpdate()
{
	Player* lp = *s_Game.m_LocalPlayer;

	if (!lp || !lp->IsAlive())
	{
		return;
	}

	if (!lp->IsMovingByKeys())
	{
		lp->m_Motion.SetX(0.0f);
		lp->m_Motion.SetZ(0.0f);

		return;
	}

	lp->SetSpeed(1.5f);
}

void Speed::OnDisable()
{
	Player* lp = *s_Game.m_LocalPlayer;

	if (!lp || !lp->IsAlive())
	{
		return;
	}

	lp->m_Motion.SetX(0.0f);
	lp->m_Motion.SetZ(0.0f);
}