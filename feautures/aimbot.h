#pragma once
#include "../math/math.h"
#include "../source/constants.h"

#define MAX_PLAYERS 32

namespace Aimbot
{
	float closest_player{ -1.0f };
	float closest_yaw{ NULL };
	float closest_pitch{ NULL };

	void get_nearest_player();

	void do_aimbot();
};
