#include <graphics/render/opengl/glcontext.hpp>
#include <graphics/window.hpp>
#include <Windows.h>
#include "../glcontextimpl.hpp"
#include "../../../win32/windowimpl.hpp"
#include "../../../opengl/win32/contextimpl.hpp"
#include "../../../../common/win32/errorcheck.hpp"

namespace mgl
{
    bool GLContext::isWindowUsed(const Ref<Window>& window) const
    {
        return wglGetCurrentDC() == WIN_CALLV(GetDC, window->getImpl()->hWnd);
    }

    void GLContext::useWindow(const Ref<Window>& window)
    {
        impl->context.getImpl()->hDC = WIN_CALLV(GetDC, window->getImpl()->hWnd);
    }

    bool GLContext::isCurrent() const
    {
        HGLRC hRC = WIN_CALLR(wglGetCurrentContext);
        return impl->context.getImpl()->hRC == hRC;
    }
}