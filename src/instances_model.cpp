#include "instances_model.h"
#include "instance_detector.h"

static std::vector<RobloxInstance> instances;

void InstancesModel::Update() {
    instances.clear();

    auto pids = InstanceDetector::GetRobloxPIDs();
    bool mainAssigned = false;

    for (DWORD pid : pids) {
        RobloxInstance inst{};
        inst.pid = pid;

        if (!mainAssigned) {
            inst.type = InstanceType::MAIN;
            inst.name = L"Main Instance";
            mainAssigned = true;
        }
        else {
            inst.type = InstanceType::ALT;
            inst.name = L"Alt Instance";
        }

        instances.push_back(inst);
    }
}

const std::vector<RobloxInstance>& InstancesModel::GetInstances() {
    return instances;
}
