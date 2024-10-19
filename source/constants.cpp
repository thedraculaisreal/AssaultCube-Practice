#include "constants.h"

extern uintptr_t exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
extern Player* local_player = *(Player**)(exe_base_address + 0x17E0A8);
extern DWORD* entity_list = (DWORD*)(exe_base_address + 0x18AC04);
extern int num_players = (*(int*)(exe_base_address + 0x191FD4));

void reset_pointers()
{
    do {

        exe_base_address = (uintptr_t)GetModuleHandle(nullptr);
        local_player = *(Player**)(exe_base_address + 0x17E0A8);
        entity_list = (DWORD*)(exe_base_address + 0x18AC04);
        num_players = (*(int*)(exe_base_address + 0x191FD4));

    } while (!exe_base_address && !local_player && !entity_list && !num_players);
}


_wglSwapBuffers original_swap_buffers = (_wglSwapBuffers)(GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers"));

_SDL_SetRelativeMouseMode originall_set_relative_mouse_mode = (_SDL_SetRelativeMouseMode)(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));