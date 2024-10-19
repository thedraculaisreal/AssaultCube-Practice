#pragma once
#include "../math/math.h"
#include "../source/constants.h"

#define MAX_PLAYERS 32

class Aimbot
{

public:

	void do_aimbot();

private:

	float closest_player{ -1.0f };
	float closest_yaw{ NULL };
	float closest_pitch{ NULL };

	void get_nearest_player();

};

inline Aimbot aimbot;