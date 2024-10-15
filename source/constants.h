#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include "gencode.h"
#include "../math/math.h"

inline uintptr_t exe_base_address;
inline Player* local_player;
inline int num_players;