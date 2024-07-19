#pragma once

#include "Vector.h"
#include "PickupItem.h"

class PickupItemsVector : public Vector<PickupItem>
{
public:
	void ForEach(std::function<void(PickupItem&)> function);
};