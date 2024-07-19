#pragma once

#include "src/utils/types/Types.h"

using namespace Types;

class PickupItem
{
public:
	enum Type : uint8
	{
		TYPE_NOTHING      = 2,
		TYPE_PISTOL_AMMO  = 3,
		TYPE_RIFLE_AMMO   = 4,
		TYPE_GRENADE      = 5,
		TYPE_HEAL         = 6,
		TYPE_HELMET_ARMOR = 7,
		TYPE_BODY_ARMOR   = 8,
		TYPE_DUALS_GUN    = 9
	};

	std::string_view GetTypeName() const;
	void Print() const;

	int16  m_PositionX; //0x0000
	int16  m_PositionZ; //0x0002
private:
	int16  _04; //0x0004
public:
	int16  m_PositionY; //0x0006
	Type   m_ItemType; //0x0008
private:
	char   _09[7]; //0x0009
public:
	bool   m_IsSpawned; //0x0010
private:
	char   _11[3]; //0x0011
public:
	uint32 m_UpdatedTime; //0x0014
}; //Size: 0x0018