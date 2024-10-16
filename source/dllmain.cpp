#include <Windows.h>
#include <iostream>
#include <thread>
#include <atomic>

#include "../feautures/nodamage.h"
#include "../feautures/aimbot.h"
#include "../classes/classes.h"
#include "detours.h"

void hook(const HMODULE hModule) noexcept
{

    Aimbot::do_aimbot();
   
    FreeLibraryAndExitThread(hModule, 0);
}

void console(const HMODULE hModule) noexcept
{
    // Allocate a new console window
    AllocConsole();

    // Redirect the standard input/output streams to the console
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

    std::cout << "Console has been allocated!" << std::endl;
    std::cout << std::hex << Aimbot::local_player << std::endl;
    std::cout << Aimbot::entity_list << std::endl;
    std::cout << Aimbot::exe_base_address << std::endl;

    while (!GetAsyncKeyState(VK_DELETE) & 0x1)
    {
        std::string input;
        std::cin >> input;

        if (input == "fish")
        {
            std::cout << "Slaguhter and  gut the efifsh";
        }

    }

    FreeConsole();

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
        const auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(console), hModule, 0, nullptr);
        if (thread)
            CloseHandle(thread);
        if (thread2)
            CloseHandle(thread2);
    }

    return 1;
}

