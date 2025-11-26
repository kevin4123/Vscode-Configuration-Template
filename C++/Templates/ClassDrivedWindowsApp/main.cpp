/**
 * @file main.cpp
 * @brief Program entry point, demonstrating file I/O functionality
 *
 * Uses the readFile and writeFile functions provided in fileio.cpp for testing.
 */

#include "MyMiniMFC.h"

class CMyApp : public MiniApp {
public:
    bool InitInstance() override {
        CreateMainWindow(L"My First MiniMFC Window");	// 4: create main window
        return true;
    }
};

CMyApp theApp;  // 1: initialize global application object,it will set itself to a global pointer
