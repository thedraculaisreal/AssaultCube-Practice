#include "aimbot.h"
#include "../source/constants.h"
#include <stdio.h>
#include <iostream>
#define M_PI 3.14159265358979323846


float euclidean_distance(float x, float y) {
    return sqrtf((x * x) + (y * y));
}

void Aimbot::aimbot()
{

    Sleep(1000);

    while (true)
    {

        // These variables will be used to hold the closest enemy to us
        float closest_player = -1.0f;
        float closest_yaw = NULL;
        float closest_pitch = NULL;

        for (auto &Player: entity_list.entities)
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

            // Calculate the yaw
            float azimuth_xy = atan2f(abspos_y, abspos_x);
            // Convert to degrees
            float yaw = (float)(azimuth_xy * (180.0 / M_PI));
            // Add 90 since the game assumes direct north is 90 degrees
            closest_yaw = yaw + 90;
            // don't look straight at the air when close to an enemy

            // Calculate the pitch
            // Since Z values are so limited, pick the larger between x and y to ensure that we 
            // don't look straight at the air when close to an enemy
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
            // Covert the value to degrees
            float pitch = (float)(azimuth_z * (180.0 / M_PI));
           
            // compares last loops enemy to new loop enemy seeing if closer 
            float temp_distance = euclidean_distance(abspos_x, abspos_y);

            if (closest_player == -1.0f || temp_distance < closest_player)
            {
                closest_player = temp_distance;
                closest_yaw = yaw + 90;
                closest_pitch = pitch;
            }

        }

        if (closest_pitch == NULL || closest_yaw == NULL)
            continue;

        if (!GetAsyncKeyState(VK_XBUTTON2))
            continue;

        local_player->pitch = closest_pitch;
        local_player->yaw = closest_yaw;

        Sleep(1);
    }
}