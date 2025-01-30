#include <graphics/opengl/context.hpp>
#include <numeric>
#include <unordered_map>
#include <glad/wgl.h>
#include <Windows.h>
#include <graphics/window.hpp>
#include "contextimpl.hpp"
#include "../../win32/windowimpl.hpp"
#include "../../win32/devicecontextimpl.hpp"
#include "../../../common/win32/errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        static std::unordered_map<HGLRC, Context*> contextMap;

        Context::Context() :
            impl(CreateOwned<ContextImpl>()) {}

        void Context::create(uint major, uint minor, ContextProfile profile)
        {
            static bool gladLoad = false;
            
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
            contextMap[impl->hRC] = this;

            makeCurrent();

            GLint maxTexUnits = getParameterInt(ContextParam::MAX_TEXTURE_IMAGE_UNITS);
            unusedTexUnits.resize(maxTexUnits);
            std::iota(unusedTexUnits.begin(), unusedTexUnits.end(), 0);
            std::reverse(unusedTexUnits.begin(), unusedTexUnits.end());
        }

        Context::~Context()
        {
            contextMap.erase(contextMap.find(impl->hRC));
            WIN_CALLV(wglDeleteContext, impl->hRC);
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

        Context* Context::getCurrent()
        {
            HGLRC hRC = WIN_CALLV(wglGetCurrentContext);
            return contextMap[hRC];
        }
    }
}