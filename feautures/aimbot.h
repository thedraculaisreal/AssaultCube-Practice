#pragma once
#include "../math/math.h"

#define MAX_PLAYERS 32

namespace Aimbot
{
	inline DWORD old_protect{ NULL };
	inline DWORD x_values[MAX_PLAYERS]{ NULL };
	inline DWORD y_values[MAX_PLAYERS]{ NULL };
	inline char* names[MAX_PLAYERS]{ NULL };
	inline DWORD ret_address{ 0x0046138D };
	inline DWORD text_address{ 0x0046E640 };
	inline const char* empty_text = " ";
	inline const char* text = "Enemy";
	inline DWORD x = 0;
	inline DWORD y = 0;

	void esp_code_cave_thread();

	void esp_code_cave();

	void do_aimbot();
};
