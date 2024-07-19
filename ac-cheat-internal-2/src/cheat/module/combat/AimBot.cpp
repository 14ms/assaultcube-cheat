#include "pch.h"

#include "AimBot.h"

static void LookAt(Player* plrA, Player* plrB)
{
	auto deltaVec = plrA->m_HeadPosition - plrB->m_HeadPosition;
	float deltaLen = deltaVec.Length();

	float pitch = -asin(deltaVec.GetY() / deltaLen) * (180.0f / 3.14f);
	float yaw = atan2(deltaVec.GetZ(), deltaVec.GetX()) * (180.0f / 3.14f);

	yaw = yaw - 90.0f;
	yaw = yaw < 0.0f ? yaw + 360.0f : yaw;

	plrA->m_CameraPitch = pitch;
	plrA->m_CameraYaw = yaw;
}

static Player* GetClosestTo(Player* plr)
{
	float closestDist = 0;
	Player* closestPlr = nullptr;

	Cheat::game.m_OtherPlayers->ForEach([&](Player& otherPlr) {
		float dist = plr->m_PositionOrigin.Distance(otherPlr.m_PositionOrigin);

		if (!otherPlr.IsAlive() || plr->IsTeamate(&otherPlr))
		{
			return;
		}

		if (!closestPlr || dist < closestDist)
		{
			closestDist = dist;
			closestPlr = &otherPlr;
		}
	});

	return closestPlr;
}

AimBot::AimBot() : Module("AimBot", 'O')
{
}

void AimBot::OnUpdate()
{
	Player* plr = *s_Game.m_LocalPlayer;

	if (plr)
	{
		Player* otherPlr = GetClosestTo(plr);

		if (otherPlr)
		{
			LookAt(plr, otherPlr);
		}
	}
}