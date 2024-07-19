#include "pch.h"

#include "PickupItemsVector.h"

void PickupItemsVector::ForEach(
	std::function<void(PickupItem&)> function)
{
	if (!m_Data)
	{
		return;
	}

	for (size_t i = 0; i < m_CurLength; i++)
	{
		PickupItem* item = GetElement(i);

		if (item->m_ItemType != PickupItem::TYPE_NOTHING)
		{
			function(*item);
		}
	}
}