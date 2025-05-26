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

BOOL WINAPI	DllMain(HINSTANCE handle, DWORD reason, LPVOID reserved) {
	if (reason == 1) { // dll process attach
		
	}

	return TRUE;
}
