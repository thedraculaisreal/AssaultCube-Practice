#include "aimbot.h"

#define M_PI 3.14159265358979323846

void Aimbot::do_aimbot()
{

    Sleep(1000);

    while (true)
    {

        // These variables will be used to hold the closest enemy to us
        float closest_player = -1.0f;
        float closest_yaw = NULL;
        float closest_pitch = NULL;

        unsigned int i = 1;

        for (auto &Player: entity_list.entities)
        {

            if (!entity_list.local_player)
                continue;

            if (!Player)
                continue;

            if (Player->health > 100 || Player->health <= 0)
                continue;
            
            float abspos_x = Player->o.x - entity_list.local_player->o.x;

            float abspos_y = Player->o.y - entity_list.local_player->o.y;

            float abspos_z = Player->o.z - entity_list.local_player->o.z;

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

            float yaw_diff = entity_list.local_player->yaw - yaw;
            float pitch_diff = entity_list.local_player->pitch - pitch;

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
            //names[i] = Player->name; doesnt work rn IDK WHY :P
           
            // compares last loops enemy to new loop enemy seeing if closer 
            float temp_distance = Math::euclidean_distance(abspos_x, abspos_y);

            if (closest_player == -1.0f || temp_distance < closest_player)
            {
                closest_player = temp_distance;
                closest_yaw = yaw + 90;
                closest_pitch = pitch;
            }

            if (i < entity_list.num_players)
            {
                i++;
            }

            if (i == entity_list.num_players)
            {
                i = 1;
            }
        }

        if (closest_pitch == NULL || closest_yaw == NULL)
            continue;

        if (!GetAsyncKeyState(VK_XBUTTON2))
            continue;

        entity_list.local_player->pitch = closest_pitch;
        entity_list.local_player->yaw = closest_yaw;

        Sleep(1);
    }
}


__declspec(naked) void Aimbot::esp_code_cave()
{

    __asm
    {
        push empty_text
        call text_address
        pushad
    }

    for (unsigned int i = 1; i <= entity_list.num_players; i++)
    {
        x = x_values[i];
        y = y_values[i];

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

void Aimbot::esp_code_cave_thread()
{
    unsigned char* hook_location = (unsigned char*)0x00461382;
    VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    *hook_location = 0xE9;
    *(DWORD*)(hook_location + 1) = (DWORD)&esp_code_cave - ((DWORD)hook_location + 5);
}