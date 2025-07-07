#include "imgui_impl_mgl.h"
#include "imgui_impl_win32.h"
#include <Windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

IMGUI_IMPL_API long ImGui_ImplMgl_WndProcHandler(void* hWnd, unsigned int msg, unsigned int wParam, long lParam)
{
    return ImGui_ImplWin32_WndProcHandler((HWND)hWnd, msg, wParam, lParam);
}