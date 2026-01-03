#pragma once
#include <Windows.h>
#include <vector>

struct RobloxInstance {
    DWORD pid;
    HWND hwnd;
    bool isPrimary;
};

class InstanceManager {
public:
    static void Start();
    static void Stop();

    static const std::vector<RobloxInstance>& GetInstances();
    static void SetPrimary(DWORD pid);

private:
    static void Scan();
};
