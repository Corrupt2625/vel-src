#include "libs/pch/pch.h"
#include <windows.h>
#include <iostream>

#pragma comment(lib, "libMinHook64x.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \ name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \ processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

DWORD_PTR FindPattern(const char* pattern, const char* mask, DWORD_PTR base, size_t size) {
    for (size_t i = 0; i < size; i++) {
        bool found = true;
        for (size_t j = 0; mask[j]; j++) {
            if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found)
            return base + i;
    }
    return NULL;
}


DWORD WINAPI MainThread(LPVOID lpParam) {
    AllocConsole();
    FILE* fp;
    freopen("CONOUT$", "w", stdout);
    std::cout << "[VelDLL] Injected successfully into Roblox!\n";

    DWORD_PTR base = (DWORD_PTR)GetModuleHandle(NULL);
    DWORD_PTR address = FindPattern("\x90\x90\x90\x90", "xxxx", base, 0x01000000);

    std::cout << "Found at: " << std::hex << address << std::endl;

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

        char RobloxPathBuffer[MAX_PATH];
        if (!GetModuleFileNameA(GetModuleHandleA(NULL), RobloxPathBuffer, MAX_PATH)) {
            MessageBoxA(NULL, "Failed to fetch critical initiation dependency! (1)", "Error!", MB_OK | MB_ICONERROR);
            exit(1);
        }
    }
    return TRUE;
}

