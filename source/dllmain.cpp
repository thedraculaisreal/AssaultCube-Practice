#include <Windows.h>
#include <iostream>
#include <thread>

#include "../feautures/nodamage.h"
#include "../feautures/aimbot.h"
#include "../classes/classes.h"


void loop()
{
    entity_list.loop();
}

void hook()
{
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

