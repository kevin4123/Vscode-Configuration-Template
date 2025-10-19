#pragma once
#include <windows.h>

class MiniApp;
extern MiniApp* g_pApp;  // global pointer to the application

class MiniApp {
public:
    HINSTANCE hInstance;
    HWND hWnd;

    MiniApp();		

    virtual bool InitInstance() = 0; // pure virtual

    virtual int Run();

    bool CreateMainWindow(const wchar_t* title);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
