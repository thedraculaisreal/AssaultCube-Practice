#include "aimbot.h"

#define M_PI 3.14159265358979323846

void Aimbot::do_aimbot()
{
    while (running)
    {
        // These variables will be used to hold the closest enemy to us
        float closest_player = -1.0f;
        float closest_yaw = NULL;
        float closest_pitch = NULL;

        player_index = 1;   

        if (entitylist.num_players == 0)
        {
            Sleep(1000);
            continue;
        }

        for (const auto &Player: entitylist.entities)
        {

            if (!entitylist.local_player)
                continue;

            if (Player == NULL || !Player)
                continue;

            if (Player->health > 100 || Player->health <= 0)
                continue;
            
            float abspos_x = Math::origin_calc(Player->o.x, entitylist.local_player->o.x);

            float abspos_y = Math::origin_calc(Player->o.y, entitylist.local_player->o.y);

            float abspos_z = Math::origin_calc(Player->o.z, entitylist.local_player->o.z);

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

            if (player_index < entitylist.num_players)
            {
                player_index++;
            }

            if (player_index >= entitylist.num_players)
            {
                player_index = 1;
            }
        }

        if (closest_pitch == NULL || closest_yaw == NULL)
            continue;

        if (!GetAsyncKeyState(VK_XBUTTON2))
            continue;

        entitylist.local_player->pitch = closest_pitch;
        entitylist.local_player->yaw = closest_yaw;

        Sleep(1);
    }
}
