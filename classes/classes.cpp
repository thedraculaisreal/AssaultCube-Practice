#include "classes.h"

void EntityList::loop()
{

	do {
		
		exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
		local_player = *(Player**)(exe_base_address + 0x17E0A8);
		entity_list = (DWORD*)(exe_base_address + 0x18AC04);

	} while (!exe_base_address && !local_player && !entity_list);


	while (true)
	{
		num_players = (*(int*)(exe_base_address + 0x191FD4)); // set each loop so if we swithc maps it can get new amount of players.

		if (num_players == 0)
		{
			entities.clear();
			continue;
		}

		std::vector<Player*> list;

		Player* enemy{ NULL };

		for (int i = 1; i <= num_players; i++)
		{
			if (i > num_players)
				continue;

			if (entitylist.num_players > 32 || entitylist.num_players <= 0)
				continue;

			DWORD* enemy_offset = (DWORD*)(*entity_list + (i * 4));
			if (!enemy_offset)
				continue;
			Player* enemy = (Player*)(*enemy_offset);
			if (!enemy)
				continue;

			list.push_back(enemy);
			Sleep(1);
		}

		entities.clear();
		entities.assign(list.begin(), list.end());
	}
}