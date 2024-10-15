#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>

#include "../feautures/nodamage.h"
#include "../feautures/aimbot.h"
#include "../classes/classes.h"

DWORD WINAPI loop(LPVOID lpParam)
{
    HMODULE hModule = (HMODULE)lpParam;

    entitylist.loop();
    
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI hook(LPVOID lpParam)
{
    HMODULE hModule = (HMODULE)lpParam;

    Sleep(1500);
    Aimbot::do_aimbot();
    
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Create the threads
        CreateThread(nullptr, 0, loop, hModule, 0, nullptr);
        CreateThread(nullptr, 0, hook, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

