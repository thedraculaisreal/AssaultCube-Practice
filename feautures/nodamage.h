#pragma once
#include <Windows.h>

namespace NoDamage
{
	void codecave();

	void codecave2();

	void injected_thread();

	void injected_thread2();

	inline DWORD old_protect{ 0 };

	inline DWORD old_protect2{ 0 };

	inline DWORD jmp_back{ 0x00484499 };

	inline DWORD jmp_back2{ 0x0041C226 };
}
