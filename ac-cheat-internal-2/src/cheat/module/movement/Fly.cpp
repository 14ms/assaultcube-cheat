#include "pch.h"

#include "Fly.h"

Fly::Fly() : Module("Fly", 'X')
{
	//m_IsEnabledByDefault = true;
}

void Fly::OnUpdate()
{
	Player* lp = *s_Game.m_LocalPlayer;

	if (!lp)
	{
		return;
	}

	if (!lp->IsAlive())
	{
		lp->m_State = Player::STATE_DEAD;

		return;
	}

	lp->m_State = Player::STATE_NOCLIP;

	if (!lp->IsMovingByKeys())
	{
		lp->m_Motion.SetX(0.0f);
		lp->m_Motion.SetZ(0.0f);
	}
	else
	{
		lp->SetSpeed(1.0f);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		lp->m_Motion.SetY(1.0f);
	}
	else if (GetAsyncKeyState(VK_SHIFT))
	{
		lp->m_Motion.SetY(-1.0f);
	}
	else
	{
		lp->m_Motion.SetY(0.0f);
	}
}

void Fly::OnDisable()
{

	Player* lp = *s_Game.m_LocalPlayer;

	if (!lp)
	{
		return;
	}

	if (!lp->IsAlive())
	{
		lp->m_State = Player::STATE_DEAD;
	}
	else
	{
		lp->m_State = Player::STATE_ALIVE;

		lp->m_Motion.SetX(0.0f);
		lp->m_Motion.SetY(0.0f);
		lp->m_Motion.SetZ(0.0f);
	}
}