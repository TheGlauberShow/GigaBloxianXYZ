#include "mutex_manager.h"

static HANDLE g_mutex = nullptr;

bool MutexManager::Acquire() {
    g_mutex = CreateMutexW(nullptr, TRUE, L"ROBLOX_singletonMutex");
    if (!g_mutex) return false;
    return true;
}

void MutexManager::Release() {
    if (g_mutex) {
        ReleaseMutex(g_mutex);
        CloseHandle(g_mutex);
        g_mutex = nullptr;
    }
}
