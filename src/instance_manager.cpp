#include "instance_manager.h"
#include <TlHelp32.h>

static std::vector<RobloxInstance> g_instances;
static HANDLE g_thread;
static bool g_running = false;

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return TRUE;

    PROCESSENTRY32 pe{};
    pe.dwSize = sizeof(pe);

    if (Process32First(snap, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                if (wcscmp(pe.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                    RobloxInstance inst{};
                    inst.pid = pid;
                    inst.hwnd = hwnd;
                    inst.isPrimary = false;

                    g_instances.push_back(inst);
                }
                break;
            }
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    return TRUE;
}

static DWORD WINAPI ScanThread(LPVOID) {
    while (g_running) {
        g_instances.clear();
        EnumWindows(EnumWindowsProc, 0);
        Sleep(2000); // escaneia a cada 2s
    }
    return 0;
}

void InstanceManager::Start() {
    g_running = true;
    g_thread = CreateThread(nullptr, 0, ScanThread, nullptr, 0, nullptr);
}

void InstanceManager::Stop() {
    g_running = false;
    if (g_thread) {
        WaitForSingleObject(g_thread, INFINITE);
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}

const std::vector<RobloxInstance>& InstanceManager::GetInstances() {
    return g_instances;
}

void InstanceManager::SetPrimary(DWORD pid) {
    for (auto& inst : g_instances) {
        inst.isPrimary = (inst.pid == pid);
    }
}
