#include "nodamage.h"

__declspec(naked) void NoDamage::codecave()
{
    __asm
    {
        pushad
        popad
        mov dword ptr ds : [edx + 0xF0] , eax
        mov eax, 0xFF
        jmp jmp_back
    }
}


__declspec(naked) void NoDamage::codecave2()
{
    __asm
    {
        pushad
        popad
        add dword ptr ds : [ebx + 0x04] , esi
        sub esi, ecx
        jmp jmp_back2
    }
}

void NoDamage::injected_thread()
{
    unsigned char* hook_location = (unsigned char*)0x0048448F;					   // where the hook starts
    VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect); // Set are permissions to read and write so we can set
    *hook_location = 0xE9;                                                         // a jump to our codecave 0xE9 = jmp in assembly
    *(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5); // formula for jmping to codecave location
    *(hook_location + 5) = 0x90;                                                  // set next line to nop
}

void NoDamage::injected_thread2()
{
    unsigned char* hook_location2 = (unsigned char*)0x0041C221;					   // where the hook starts
    VirtualProtect((void*)hook_location2, 5, PAGE_EXECUTE_READWRITE, &old_protect2); // Set are permissions to read and write so we can set
    *hook_location2 = 0xE9;                                                         // a jump to our codecave 0xE9 = jmp in assembly
    *(DWORD*)(hook_location2 + 1) = (DWORD)&codecave2 - ((DWORD)hook_location2 + 5); // formula for jmping to codecave location
    //*(hook_location2 + 5) = 0x90;
}
