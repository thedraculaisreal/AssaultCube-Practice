#pragma once
#include <Windows.h>
#include <vector>
#include "../classes/classes.h"

extern uintptr_t exe_base_address;
extern Player* local_player;
extern DWORD* entity_list;
extern int num_players;

void reset_pointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers original_swap_buffers;

typedef int(__fastcall* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode originall_set_relative_mouse_mode;