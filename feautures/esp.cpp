#include "esp.h"

#define M_PI 3.14159265358979323846
#define MAX_PLAYERS 32

__declspec(naked) void ESP::code_cave()
{

	__asm
	{
		push empty_text
		call text_address
		pushad
	}

	for (int i = 0; i < num_players; i++)
	{
		x = 1200; //x_values[i];
		y = 900; //y_values[i];
		text = "Enemy";

		if (x > 2400 || x < 0 || y < 0 || y > 1800)
		{
			text = "";
		}

		x_values[i] += 200;

		if (text == NULL)
		{
			continue;
		}

		__asm
		{
			push y
			push x
			push text
			call text_address
			add esp, 0xC
		}

		Sleep(1);
	}

	__asm
	{
		popad
		jmp ret_address
	}

}

void ESP::code_cave_thread()
{

	unsigned char* hook_location = (unsigned char*)0x00461382;
	VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
	*hook_location = 0xE9;
	*(DWORD*)(hook_location + 1) = (DWORD)&code_cave - ((DWORD)hook_location + 5);
}

void ESP::injected_thread()
{

	Sleep(1000);

	while (true)
	{
		float closest_player = -1.0f;
		float closest_yaw = NULL;
		float closest_pitch = NULL;

		int i = 0;

		for (auto &Player : entity_list.entities)
		{

			if (!local_player)
				continue;

			if (!Player)
				continue;

			if (Player->health > 100 || Player->health <= 0)
				continue;

			float abspos_x = Player->o.x - local_player->o.x;
			 
			float abspos_y = Player->o.y - local_player->o.y;

			float abspos_z = Player->o.z - local_player->o.z;

			float azimuth_xy = atan2f(abspos_y, abspos_x);

			float azimuth_z = atan2f(abspos_z, abspos_y);

			float yaw = (float)(azimuth_xy * (180.0 / M_PI));
			float pitch = (float)(azimuth_z * (180.0 / M_PI));

			yaw = yaw + 90.0f;

			float yaw_diff = local_player->yaw - yaw;
			float pitch_diff = local_player->pitch - pitch;

			if (yaw_diff > 180)
				yaw_diff -= 360;
			if (yaw_diff < -180)
				yaw_diff -= yaw_diff + 360;

			if (pitch_diff > 90)
				pitch_diff -= 180;
			if (pitch_diff < -90)
				pitch_diff += 180;

			x_values[i] = (DWORD)(1200 + (yaw_diff * -30));
			y_values[i] = (DWORD)(900 + (pitch_diff * 25));

			Sleep(1);

			i++;
		}
	}
}