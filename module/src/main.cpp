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

BOOL WINAPI	DllMain(HINSTANCE handle, DWORD reason, LPVOID reserved) {
	if (reason == 1) { // dll process attach
		
	}

	return TRUE;
}
