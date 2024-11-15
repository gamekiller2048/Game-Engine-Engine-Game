#include <input/input.hpp>
#include <common/win32/errors.hpp>
#include <Windows.h>
#include "../../common/win32/errorcheck.hpp"

namespace mil
{
    mml::vec2 getMousePos()
    {
        POINT p;
        WIN_CALL(GetCursorPos, &p);
        return mml::vec2((float)p.x, (float)p.y);
    }

    void setMousePos(const mml::ivec2& pos)
    {
        WIN_CALL(SetCursorPos, pos.x, pos.y);
    }

    bool isKeyPressed(Key key)
    {
        return WIN_CALLR(GetKeyState, (int)key) & 0x8000;
    }

    bool isMousePressed(Mouse button)
    {
        return WIN_CALLR(GetKeyState, (int)button) & 0x8000;
    }
}