#include <Windows.h>
#include <iostream>
#include <thread>
#include "constants.h"
#include "../feautures/nodamage.h"
#include "../feautures/aimbot.h"


void loop()
{
    entity_list.loop();
}

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

void hook()
{
    
    exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
    local_player = *(Player**)(exe_base_address + 0x17E0A8);
    Aimbot::do_aimbot();
     
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, NULL, nullptr);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)loop, nullptr, NULL, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

