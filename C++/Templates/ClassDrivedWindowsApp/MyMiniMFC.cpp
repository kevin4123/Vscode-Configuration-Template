#include "MyMiniMFC.h"

MiniApp* g_pApp = nullptr;  // global pointer to the application

MiniApp::MiniApp() {		
    g_pApp = this;			// 2: set the global pointer,only one instance per process
}

int MiniApp::Run() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

bool MiniApp::CreateMainWindow(const wchar_t* title) {
    const wchar_t* className = L"MiniMFCWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClass(&wc);

    hWnd = CreateWindowEx(
        0, className, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return false;

    ShowWindow(hWnd, SW_SHOW);
    return true;
}

LRESULT CALLBACK MiniApp::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ========== WinMain ==========
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    if (g_pApp == nullptr)
        return -1;

    g_pApp->hInstance = hInstance;		// 3:set the application instance

    if (!g_pApp->InitInstance())		// 4: initialize the application and create main window
        return -1;

    return g_pApp->Run();				// 5: run the application,main message loop
}
