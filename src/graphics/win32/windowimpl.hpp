#pragma once
#include <Windows.h>

namespace mgl
{
    class WindowImpl
    {
    public:
        HWND hWnd;
        static LRESULT windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}