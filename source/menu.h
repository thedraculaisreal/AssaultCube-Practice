#pragma once
#include <Windows.h>

namespace Menu
{
	void toggle_menu();
	void init();
	void start_render();
	void render();
	void end_render();
	BOOL __stdcall new_swap_buffers(HDC hdc);
}
