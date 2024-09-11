#include <graphics/win32/glcontext.hpp>
#include <glad/wgl.h>
#include <Windows.h>
#include <graphics/win32/window.hpp>
#include "glcontextimpl.hpp"
#include "windowimpl.hpp"
#include "devicecontextimpl.hpp"
#include "errorcheck.hpp"

namespace mgl
{
	namespace win32
	{
        GLContext::GLContext(const mgl::Window* window, uint major, uint minor) :
            mgl::GLContext(major, minor), impl(CreateOwned<GLContextImpl>())
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
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
            };

            impl->hRC = WIN_CALLV(wglCreateContextAttribsARB, impl->hDC, NULL, attribs);
        }

        GLContext::~GLContext()
        {
            WIN_CALLV(wglDeleteContext, impl->hRC);
        }

        void GLContext::useWindow(const mgl::Window* window)
        {
            const Window* win = static_cast<const Window*>(window);
            impl->hDC = WIN_CALLV(GetDC, win->getImpl()->hWnd);
        }

        void GLContext::makeCurrent()
        {
            WIN_CALLV(wglMakeCurrent, impl->hDC, impl->hRC);
        }

        void GLContext::swapBuffers()
        {
            WIN_CALLV(SwapBuffers, impl->hDC);
        }

        bool GLContext::isCurrent() const
        {
            HGLRC hRC = WIN_CALLR(wglGetCurrentContext);
            return impl->hRC == hRC;
        }
	}
}