#pragma once
#include <Windows.h>

namespace CpuAffinity {
    bool SetAffinity(DWORD pid, DWORD_PTR mask);
    bool SetPriority(DWORD pid, DWORD priority);
}
