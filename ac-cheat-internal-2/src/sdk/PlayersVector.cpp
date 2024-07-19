#include "pch.h"

#include "PlayersVector.h"

void PlayersVector::ForEach(std::function<void(Player&)> function)
{
	if (!m_Data)
	{
		return;
	}

	for (size_t i = 0; i < m_CurLength; i++)
	{
		Player** plr = GetElement(i);

		if (*plr)
		{
			function(**plr);
		}
	}
}