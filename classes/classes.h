#pragma once
#include <cstdio>
#include <iostream>
#include <vector>
#include <Windows.h>

inline bool running{ true };

class Vector3
{
public:
    float x, y, z;
};

class Player
{
public:
    void* vtable;
    Vector3 o; //0x0004
    char pad_0010[24]; //0x0010
    Vector3 pos; //0x0028
    float yaw; //0x0034
    float pitch; //0x0038
    float roll; //0x003C
    char pad_0040[172]; //0x0040
    int32_t health; //0x00EC
    char pad_00F0[278]; //0x00F0
    char name[16]; //0x0204
    char pad_0208[256]; //0x0208
    int32_t Team; //0x0308
}; //Size: 0x0450

class EntityList
{
public:

    uintptr_t exe_base_address{ NULL };
    Player* local_player{ NULL };
    unsigned int num_players{ NULL };
    DWORD* entity_list{ NULL };


    std::vector<Player*> entities{ 0 };

    void loop();
};

inline EntityList entitylist;