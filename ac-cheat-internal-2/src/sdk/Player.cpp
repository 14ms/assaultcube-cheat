#include "pch.h"

#include "Player.h"

bool Player::IsTeamate(Player* plr) const
{
	return m_Team == plr->m_Team;
}

bool Player::IsTeamate(const Player& plr) const
{
	return m_Team == plr.m_Team;
}

bool Player::IsMovingByKeys() const
{
	return m_IsMovingForward || m_IsMovingBack || m_IsMovingLeft || m_IsMovingRight;
}

bool Player::IsAlive() const
{
	return m_Health > 0;
}

void Player::Print() const
{
	std::cout << "Player<" << this << "> " << m_Username << '\n';
}

void Player::SetSpeed(float speed)
{
	float yaw = 0.0f;

	if (m_IsMovingForward)
	{
		if (m_IsMovingLeft)
		{
			yaw -= 45;
		}
		else if (m_IsMovingRight)
		{
			yaw += 45;
		}
	}
	else if (m_IsMovingBack)
	{
		yaw -= 180;

		if (m_IsMovingLeft)
		{
			yaw += 45;
		}
		else if (m_IsMovingRight)
		{
			yaw -= 45;
		}
	}
	else
	{
		if (m_IsMovingLeft)
		{
			yaw -= 90;
		}
		else if (m_IsMovingRight)
		{
			yaw += 90;
		}
	}

	float xDir = sin((m_CameraYaw + yaw) * (3.14f / 180.0f));
	float zDir = -cos((m_CameraYaw + yaw) * (3.14f / 180.0f));

	m_Motion.SetX(xDir * speed);
	m_Motion.SetZ(zDir * speed);
}