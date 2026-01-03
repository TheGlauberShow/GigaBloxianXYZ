#include <Windows.h>

#include "mutex_manager.h"
#include "tray_app.h"
#include "instance_manager.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {

    // Libera múltiplas instâncias
    if (!MutexManager::Acquire()) {
        MessageBox(nullptr, L"Failed to acquire Roblox mutex", L"GigaBloxianXYZ", MB_ICONERROR);
        return 1;
    }

    // Tray app
    if (!TrayApp::Init(hInst)) {
        MutexManager::Release();
        return 1;
    }

    // Inicia gerenciamento automático de instâncias
    InstanceManager::Start();

    // Loop principal (tray)
    TrayApp::Run();

    // Cleanup
    InstanceManager::Stop();
    TrayApp::Shutdown();
    MutexManager::Release();

    return 0;
}
