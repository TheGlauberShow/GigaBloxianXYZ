#include "instance_manager.h"
#include "instance_detector.h"
#include "cpu_affinity.h"

#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>

static std::atomic<bool> running = false;
static std::thread worker;

static DWORD_PTR GetAllCoresMask() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (1ULL << si.dwNumberOfProcessors) - 1;
}

void Loop() {
    DWORD_PTR allCores = GetAllCoresMask();

    while (running) {
        auto pids = InstanceDetector::GetRobloxPIDs();

        if (!pids.empty()) {
            std::sort(pids.begin(), pids.end());

            DWORD mainPid = pids[0];

            // MAIN instance
            CpuAffinity::SetPriority(mainPid, HIGH_PRIORITY_CLASS);
            CpuAffinity::SetAffinity(mainPid, allCores);

            // ALT instances
            for (size_t i = 1; i < pids.size(); i++) {
                CpuAffinity::SetPriority(pids[i], BELOW_NORMAL_PRIORITY_CLASS);

                // Limita ALT a metade dos cores
                DWORD_PTR mask = allCores >> 1;
                if (mask == 0) mask = 1;
                CpuAffinity::SetAffinity(pids[i], mask);
            }
        }

        Sleep(3000); // atualiza a cada 3 segundos
    }
}

void InstanceManager::Start() {
    if (running) return;
    running = true;
    worker = std::thread(Loop);
}

void InstanceManager::Stop() {
    running = false;
    if (worker.joinable())
        worker.join();
}
