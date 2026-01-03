#include "instance_detector.h"
#include <TlHelp32.h>

std::vector<DWORD> InstanceDetector::GetRobloxPIDs() {
    std::vector<DWORD> result;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return result;

    PROCESSENTRY32 pe{};
    pe.dwSize = sizeof(pe);

    if (Process32First(snap, &pe)) {
        do {
            if (wcscmp(pe.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                result.push_back(pe.th32ProcessID);
            }
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    return result;
}
