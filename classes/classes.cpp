#include "classes.h"

void EntityList::loop()
{


    while (true)
    {
        num_players = (*(int*)(exe_base_address + 0x191FD4));
        exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
        local_player = *(Player**)(exe_base_address + 0x17E0A8);

        for (int i = 1; i <= num_players; i++)
        {
            if (num_players == 0)
                continue;

            DWORD* entity_list = (DWORD*)(exe_base_address + 0x18AC04);
            if (!entity_list)
                continue;
            DWORD* enemy_offset = (DWORD*)(*entity_list + (i * 4));
            if (!enemy_offset)
                continue;
            Player* enemy = (Player*)(*enemy_offset);
            if (!enemy)
                continue;

            entities.push_back(enemy);
        }

        Sleep(10);
    }
}