#pragma once
#include "../source/constants.h"
#define MAX_PLAYERS 32

namespace ESP
{

	void injected_thread();
	void code_cave();
	void code_cave_thread();


	inline DWORD old_protect{ NULL };

	inline DWORD x_values[MAX_PLAYERS] = { 0 };
	inline DWORD y_values[MAX_PLAYERS] = { 0 };
	//inline char* names[MAX_PLAYERS] = { 0 };
	inline DWORD ret_address{ 0x0046138D };
	inline DWORD text_address{ 0x0046E640 };
	inline const char* empty_text = " ";
	inline const char* text = "";
	inline DWORD x = 0;
	inline DWORD y = 0;

}