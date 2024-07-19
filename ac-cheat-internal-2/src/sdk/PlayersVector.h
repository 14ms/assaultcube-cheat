#pragma once

#include "Vector.h"
#include "Player.h"

class PlayersVector : public Vector<Player*>
{
public:
	void ForEach(std::function<void(Player&)> function);
};