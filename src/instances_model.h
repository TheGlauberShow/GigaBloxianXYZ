#pragma once
#include <Windows.h>
#include <string>

struct RobloxInstance {
    DWORD pid;
    std::wstring name;
    bool isMain;

    RobloxInstance(DWORD p)
        : pid(p), name(L"Roblox Instance"), isMain(false) {}
};
