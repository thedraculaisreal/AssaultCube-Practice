#pragma once
#include "../math/math.h"
#include "../classes/classes.h"

#define MAX_PLAYERS 32

namespace Aimbot
{

	inline uintptr_t exe_base_address;

	inline Player* local_player;

	inline DWORD* entity_list;

	inline int num_players;

	void do_aimbot();

};
