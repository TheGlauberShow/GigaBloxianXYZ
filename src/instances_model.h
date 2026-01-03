#pragma once
#include <Windows.h>
#include <string>
#include <vector>

enum class InstanceType {
    MAIN,
    ALT
};

struct RobloxInstance {
    DWORD pid;
    InstanceType type;
    std::wstring name;
};

namespace InstancesModel {
    void Update();
    const std::vector<RobloxInstance>& GetInstances();
}
