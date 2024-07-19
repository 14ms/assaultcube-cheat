#pragma once

#include "src/utils/types/Types.h"

class Player;

using namespace Types;

class ItemInfo
{
public:
	char   m_ItemType[20]; //0x0000
private:
	uint16 _14; //0x0014
	uint8  _16; //0x0016
public:
	char   m_ItemName[20]; //0x0017
private:
	char   _2B[28]; //0x002B
	uint32 _47;     //0x0047
	char   _4B[4];  //0x004B
	uint16 _4F;     //0x004F
	uint8  _51;     //0x0051
	uint8  _52;     //0x0052
	uint8  _53;     //0x0053
	uint8  _54;     //0x0054
	char   _55[1];  //0x0055
public:
	uint8  m_MaxClipAmmo; //0x0056
private:
	char   _57[15]; //0x0057
public:
	uint16 m_IsAutomatic; //0x0066
}; //Size: 0x0068

class Item
{
private:
	void* m_VTable;
public:
	uint32    m_WeaponIndex;  //0x0004
	Player*   m_Owner;        //0x0008
	ItemInfo* m_ItemInfo;     //0x000C
	uint32*   m_MagAmmo;      //0x0010
	uint32*   m_ClipAmmo;     //0x0014
	uint32*   m_ShootDelay;   //0x0018
	uint32    m_BulletsFired; //0x001C
	uint32    m_ReloadTime;   //0x0020
}; //Size: 0x0024