#include "pch.h"

#include "FOV.h"

FOV::FOV() : Module("FOV", 'C')
{
}

void FOV::OnUpdate()
{
	*s_Game.m_CameraFov = 150;
}

void FOV::OnEnable()
{
	m_OldFov = *s_Game.m_CameraFov;
}

void FOV::OnDisable()
{
	*s_Game.m_CameraFov = m_OldFov;
}