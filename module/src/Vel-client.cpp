#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

DWORD GetProcessIdByName(const wchar_t* processName) {
    PROCESSENTRY32W entry = { 0 };
    entry.dwSize = sizeof(entry);
    DWORD pid = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (!_wcsicmp(entry.szExeFile, processName)) {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return pid;
}

bool InjectDLL(DWORD pid, const wchar_t* dllPath) {
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc) return false;

    size_t size = (wcslen(dllPath) + 1) * sizeof(wchar_t);
    void* alloc = VirtualAllocEx(hProc, nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!alloc) return false;

    WriteProcessMemory(hProc, alloc, dllPath, size, nullptr);
    HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW"),
        alloc, 0, nullptr);

    if (hThread) CloseHandle(hThread);
    CloseHandle(hProc);
    return hThread != nullptr;
}

int main() {
    const wchar_t* dllPath = L"C:\\path\\VelDLL.dll"; //blinx you can handle this
    const wchar_t* targetProcess = L"RobloxPlayerBeta.exe";

    DWORD pid = GetProcessIdByName(targetProcess);
    if (!pid) {
        std::wcerr << L"[!] Roblox is not running.\n";
        return 1;
    }

    std::wcout << L"[+] Found Roblox PID: " << pid << "\n";

    if (InjectDLL(pid, dllPath)) {
        std::wcout << L"[+] DLL Injected successfully.\n";
    }
    else {
        std::wcerr << L"[!] DLL Injection failed.\n";
    }

    return 0;
}
