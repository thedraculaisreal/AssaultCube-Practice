#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>

#include "../feautures/nodamage.h"
#include "../feautures/aimbot.h"
#include "../classes/classes.h"

void loop(const HMODULE hModule) noexcept
{
    entitylist.loop();
    
    FreeLibraryAndExitThread(hModule, 0);
}

void hook(const HMODULE hModule) noexcept
{
    Sleep(1500);

    Aimbot::do_aimbot();

    Sleep(1000);
   
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == 1)
    {
        DisableThreadLibraryCalls(hModule);
        const auto thread2 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(hook), hModule, 0, nullptr);
        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(loop), hModule, 0, nullptr);
        if (thread)
            CloseHandle(thread);
        if (thread2)
            CloseHandle(thread2);
    }

    return 1;
}

