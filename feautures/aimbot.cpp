#include "aimbot.h"

#define M_PI 3.14159265358979323846

void Aimbot::get_nearest_player()
{

	for (int i = 1; i <= num_players; i++)
	{
		DWORD* enemy_offset = (DWORD*)(*entity_list + (i * 4));
		if (!enemy_offset)
			continue;
		Player* enemy = (Player*)(*enemy_offset);
		if (!enemy)
			continue;

		if (!local_player)
			continue;

		if (enemy->health > 100 || enemy->health <= 0)
			continue;

		float abspos_x = Math::origin_calc(enemy->o.x, local_player->o.x);

		float abspos_y = Math::origin_calc(enemy->o.y, local_player->o.y);

		float abspos_z = Math::origin_calc(enemy->o.z, local_player->o.z);

		float azimuth_xy = atan2f(abspos_y, abspos_x);

		float yaw = Math::radians_to_degrees(azimuth_xy);
		closest_yaw = yaw + 90;

		if (abspos_y < 0) {
			abspos_y *= -1;
		}
		if (abspos_y < 5) {
			if (abspos_x < 0) {
				abspos_x *= -1;
			}
			abspos_y = abspos_x;
		}

		float azimuth_z = atan2f(abspos_z, abspos_y);
		float pitch = Math::radians_to_degrees(azimuth_z);

		float temp_distance = Math::euclidean_distance(abspos_x, abspos_y);

		if (closest_player == -1.0f || temp_distance < closest_player)
		{
			closest_player = temp_distance;
			closest_yaw = yaw + 90;
			closest_pitch = pitch;
		}
	}

}

void Aimbot::do_aimbot()
{
	get_nearest_player();

	if (closest_pitch == NULL || closest_yaw == NULL)
		return;

	if (!GetAsyncKeyState(VK_XBUTTON2))
		return;

	local_player->pitch = closest_pitch;
	local_player->yaw = closest_yaw;

	Sleep(1);
}