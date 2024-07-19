#pragma once

#include "src/utils/Mem.h"

#include "src/sdk/Player.h"
#include "src/sdk/PlayersVector.h"
#include "src/sdk/PickupItemsVector.h"

class Game
{
public:
	enum MenuState : uint8
	{
		MENU_STATE_IN_GAME,
		MENU_STATE_IN_LEADERBOARD,
		MENU_STATE_IN_MENU
	};

	typedef Player* (*t_GetLookingEntity)();

	uintptr_t m_ClientBase = 0;

	Player**           m_LocalPlayer = nullptr;
	PlayersVector*     m_OtherPlayers = nullptr;
	PickupItemsVector* m_PickupItems = nullptr;
	bool*              m_IsPlayingOnline = nullptr;
	uint32*            m_PlayersAmount = nullptr;
	float*             m_CameraFov = nullptr;
	float*             m_ModelMatrix = nullptr;
	float*             m_ProjMatrix = nullptr;
	MenuState*         m_MenuState = nullptr;
	void*              m_CurrentMenu = nullptr;

	t_GetLookingEntity GetLookingEntity = nullptr;

	bool Init()
	{
		auto [base, errCode] = Mem::FindModuleBase(0, L"ac_client.exe");

		if (errCode || !base)
		{
			return false;
		}

		m_ClientBase = (uintptr_t)base;

		m_LocalPlayer     = (Player**)(m_ClientBase + 0x18AC00);
		m_OtherPlayers    = (PlayersVector*)(m_ClientBase + 0x18AC04);
		m_PickupItems     = (PickupItemsVector*)(m_ClientBase + 0x19086C);
		m_IsPlayingOnline = (bool*)(m_ClientBase + 0x17F367);
		m_PlayersAmount   = (uint32*)(m_ClientBase + 0x1837E0);
		m_CameraFov       = (float*)(m_ClientBase + 0x18A7CC);
		m_ModelMatrix     = (float*)(m_ClientBase + 0x17DFD0);
		m_ProjMatrix      = (float*)(m_ClientBase + 0x17E0B0);
		m_MenuState       = (MenuState*)(m_ClientBase + 0x18587C);
		m_CurrentMenu     = (void*)(m_ClientBase + 0x185884);

		GetLookingEntity  = (t_GetLookingEntity)(m_ClientBase + 0x0CC890);

		return true;
	}
};