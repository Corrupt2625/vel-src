#include <Windows.h>
#include <Richedit.h>
#include <CommCtrl.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \ name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \ processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

DWORD WINAPI MainThread(LPVOID lpParam)
{
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{   //attach
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
