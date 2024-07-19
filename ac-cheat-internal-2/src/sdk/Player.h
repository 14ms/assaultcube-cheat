#pragma once

#include "src/utils/types/Types.h"

#include "Item.h"

using namespace Types;

class Player
{
public:
	enum Team : uint8
	{
		TEAM_CLA,
		TEAM_RVSF,
		TEAM_UNKNOWN, // ???
		TEAM_UNKNOWN_2, // ???
		TEAM_SPEC
	};

	enum State : uint8
	{
		STATE_ALIVE,
		STATE_DEAD,
		STATE_UNKNOWN, // ???
		STATE_EMOTE,   // ?
		STATE_NOCLIP,
		STATE_GHOST
	};

	static const uint32 MAX_HEALTH = 100;
	static const uint32 MAX_ARMOR  = 100;

	bool IsTeamate(Player* plr) const;
	bool IsTeamate(const Player& plr) const;
	bool IsMovingByKeys() const;
	bool IsAlive() const;
	void Print() const;

	void SetSpeed(float speed);

private:
	void*  m_VTable; //0x0000
public:
	vec3f  m_HeadPosition;       //0x0004
	vec3f  m_Motion;             //0x0010
	vec3f  m_Motion2;            //0x001C
	vec3f  m_PositionOrigin;     //0x0028
	float  m_CameraYaw;          //0x0034
	float  m_CameraPitch;        //0x0038
	float  m_CameraRoll;         //0x003C
	float  m_RecoilFactor;       //0x0040
	float  m_MotionFactor;       //0x0044 max: 16.5?
	uint32 m_TimeInAir;          //0x0048
	float  m_HitboxWidth;        //0x004C
	float  m_CurrentModelHeight; //0x0050
	float  m_MaxModelHeight;     //0x0054
	float  m_SomeHeight;         //0x0058
private:
	uint8  _5C; //0x005C
public:
	bool   m_isOnGround; //0x005D
private:
	bool   _5E; //0x005E
public:
	bool   m_HasJumped; //0x005F
private:
	uint8  _60; //0x0060 ???
public:
	bool   m_IsCrouching;      //0x0061
	bool   m_IsCrouchingInAir; //0x0062
	bool   m_IsCrouching2;     //0x0063
private:
	uint8  _64; //0x0064 ???
public:
	bool   m_IsNotMoving; //0x0065
	bool   m_IsZooming;   //0x0066
private:
	char   _67[1]; //0x0067
	uint32 _68;    //0x0068 время?
	uint32 _6C;    //0x006C ???
	uint32 _70;    //0x0070 ???
public:
	int8   m_Forward; //0x0074
	int8   m_Strafe;  //0x0075
	State  m_State;   //0x0076
private:
	bool   _77; //0x0077
	uint32 _78; //0x0078 ???
	uint32 _7C; //0x007C ???
public:
	bool   m_IsMovingLeft;    //0x0080
	bool   m_IsMovingRight;   //0x0081
	bool   m_IsMovingForward; //0x0082
	bool   m_IsMovingBack;    //0x0083
private:
	char   _84[96]; //0x0084
	uint32 _E4;     //0x00E4
	void*  _E8;     //0x00E8 ???
public:
	int32  m_Health; //0x00EC
	int32  m_Armor;  //0x00F0
private:
	char   _F4[12]; //0x00F4
public:
	uint8  m_HasDuals; //0x0100
private:
	char   _101[7]; //0x0101
public:
	uint32 m_WeaponsMagAmmo[9];      //0x0108 7: grenade 8: duals, 9: knife
	uint32 m_WeaponsClipAmmo[9];     //0x012C 7: grenade 8: duals, 9: knife
	uint32 m_WeaponsShootDelay[9];   //0x0150 7: grenade 8: duals, 9: knife
	uint32 m_WeaponsBulletsFired[9]; //0x0174 7: grenade 8: duals, 9: knife
private:
	char   _198[32]; //0x0198
public:
	uint32 m_CurrentModelSkin;  //0x01B8 range: [0, 3]
	uint32 m_SelectedModelSkin; //0x01BC range: [0, 3]
private:
	char   _pad_01C0[4]; //0x01C0
	uint32_t _N000000C0; //0x01C4
	char   _pad_01C8[8]; //0x01C8
public:
	uint32_t m_Ping; //0x01D0
private:
	char   _pad_01D4[8]; //0x01D4
public:
	int32  m_FragsScore; //0x01DC
private:
	char   _1E0[4]; //0x01E0
public:
	int32  m_DeathsScore; //0x01E4
private:
	char   _1E8[4]; //0x01E8
public:
	uint32 m_ItemUpdatedTime; //0x01EC
private:
	uint32 _1F0;     //0x01F0
	char   _1F4[16]; //0x01F4
public:
	bool   m_IsShooting;   //0x0204
	char   m_Username[16]; //0x0205
private:
	char   _215[245]; //0x0215
	uint8  _30A;      //0x030A
	uint8  _30B;      //0x030B
public:
	Team   m_Team; //0x030C
private:
	char   _30D[3]; //0x030D
	uint32 _310;    //0x0310
	uint8  _314;    //0x0314
	uint8  _315;    //0x0315
	char   _316[2]; //0x0316
public:
	bool   m_IsDead; //0x0318
private:
	char   _319[68]; //0x0319
	uint8  _35D;     //0x035D
	char   _35E[2];  //0x035E
public:
	Item*  m_OldItem;     //0x0360
	Item*  m_CurrentItem; //0x0364
}; //Size: 0x0368