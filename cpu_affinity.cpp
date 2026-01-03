#include "cpu_affinity.h"

bool CpuAffinity::SetAffinity(DWORD pid, DWORD_PTR mask) {
    HANDLE h = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (!h) return false;
    bool ok = SetProcessAffinityMask(h, mask);
    CloseHandle(h);
    return ok;
}

bool CpuAffinity::SetPriority(DWORD pid, DWORD priority) {
    HANDLE h = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (!h) return false;
    bool ok = SetPriorityClass(h, priority);
    CloseHandle(h);
    return ok;
}
