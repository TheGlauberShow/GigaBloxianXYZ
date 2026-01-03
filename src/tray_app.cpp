#include "tray_app.h"

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT 1001

static NOTIFYICONDATA nid{};
static HWND hwnd;

LRESULT CALLBACK WndProc(HWND h, UINT msg, WPARAM w, LPARAM l) {
    if (msg == WM_TRAYICON && l == WM_RBUTTONUP) {
        HMENU menu = CreatePopupMenu();
        AppendMenu(menu, MF_STRING, ID_TRAY_EXIT, L"Exit");
        POINT p; GetCursorPos(&p);
        SetForegroundWindow(h);
        TrackPopupMenu(menu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, h, nullptr);
        DestroyMenu(menu);
    }
    else if (msg == WM_COMMAND && LOWORD(w) == ID_TRAY_EXIT) {
        PostQuitMessage(0);
    }
    return DefWindowProc(h, msg, w, l);
}

bool TrayApp::Init(HINSTANCE hInstance) {
    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"GigaBloxianXYZ";
    RegisterClass(&wc);

    hwnd = CreateWindow(wc.lpszClassName, L"", 0, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcscpy_s(nid.szTip, L"GigaBloxianXYZ");

    return Shell_NotifyIcon(NIM_ADD, &nid);
}

void TrayApp::Run() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void TrayApp::Shutdown() {
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
