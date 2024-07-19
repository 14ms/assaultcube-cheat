#include "pch.h"

#include "PickupItem.h"

std::string_view PickupItem::GetTypeName() const
{
	switch (m_ItemType)
	{
	case TYPE_PISTOL_AMMO:
		return "Pistol Ammo";

	case TYPE_RIFLE_AMMO:
		return "Rifle Ammo";

	case TYPE_GRENADE:
		return "Grenade";

	case TYPE_HEAL:
		return "Heal";

	case TYPE_HELMET_ARMOR:
		return "Helmet Armor";

	case TYPE_BODY_ARMOR:
		return "Body Armor";

	case TYPE_DUALS_GUN:
		return "Duals Gun";

	default:
		return "?";
	}
}

void PickupItem::Print() const
{
	std::cout << "PickupItem<" << this << "> " << (int)m_ItemType << ' ' << GetTypeName() << '\n';
}