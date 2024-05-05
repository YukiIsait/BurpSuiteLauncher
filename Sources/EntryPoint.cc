#include <Windows.h>
#include <stdexcept>
#include "EntryPoint.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    try {
        Main();
    } catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "Failed to launch Burp Suite", MB_ICONERROR);
        return 1;
    }
    return 0;
}
