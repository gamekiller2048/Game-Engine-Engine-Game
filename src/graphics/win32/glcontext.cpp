#include <graphics/opengl/context.hpp>
#include <glad/wgl.h>
#include <Windows.h>
#include <graphics/window.hpp>
#include "glcontextimpl.hpp"
#include "windowimpl.hpp"
#include "devicecontextimpl.hpp"
#include "../../common/win32/errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        Context::Context(Window* window, uint major, uint minor, ContextProfile profile) :
            major(major), minor(minor), profile(profile), impl(CreateOwned<ContextImpl>())
        {
            create(window);
        }

        void Context::create(Window* window)
        {
            static bool gladLoad = false;

            useWindow(window);

            if(!gladLoad) {
                HGLRC tempHRC = WIN_CALLV(wglCreateContext, impl->hDC);
                WIN_CALL(wglMakeCurrent, impl->hDC, tempHRC);

                gladLoaderLoadWGL(impl->hDC);
                gladLoaderLoadGL();
                gladLoad = true;

                // TODO: figure out why this fails
                WIN_CALL(wglDeleteContext, tempHRC);
            }

            int attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, (int)major,
                WGL_CONTEXT_MINOR_VERSION_ARB, (int)minor,
                WGL_CONTEXT_PROFILE_MASK_ARB,
                profile == ContextProfile::CORE ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0
            };

            impl->hRC = WIN_CALLV(wglCreateContextAttribsARB, impl->hDC, NULL, attribs);
        }

        Context::~Context()
        {
            WIN_CALLV(wglDeleteContext, impl->hRC);
        }

        void Context::useWindow(const mgl::Window* window)
        {
            const Window* win = static_cast<const Window*>(window);
            impl->hDC = WIN_CALLV(GetDC, win->getImpl()->hWnd);
        }

        void Context::makeCurrent()
        {
            WIN_CALLV(wglMakeCurrent, impl->hDC, impl->hRC);
        }

        void Context::swapBuffers()
        {
            WIN_CALLV(SwapBuffers, impl->hDC);
        }

        bool Context::isCurrent() const
        {
            HGLRC hRC = WIN_CALLR(wglGetCurrentContext);
            return impl->hRC == hRC;
        }

        bool Context::isWindowUsed(const mgl::Window* window) const
        {
            const Window* win = static_cast<const Window*>(window);
            return wglGetCurrentDC() == WIN_CALLV(GetDC, win->getImpl()->hWnd);
        }
    }
}