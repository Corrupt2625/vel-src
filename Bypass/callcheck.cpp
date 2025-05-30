#include "callcheck.hpp"

int callchecksave(DWORD lain);

DWORD OGcall;
DWORD fallbck;
DWORD Arith;

__declspec(dllimport) void HookFUNC()
{
    __asm {
        mov eax, [esp]
        cmp eax, Arith
        jne normal_case

        add esp, 4
        call [OGcall]
        add esp, 4
        retn

    normal_case:
        jmp [fallbck]
    }
}

};
