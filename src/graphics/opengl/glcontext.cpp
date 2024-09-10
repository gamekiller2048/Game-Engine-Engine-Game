#include <graphics/opengl/glcontext.hpp>
#ifdef _WIN32
#include <graphics/win32/glcontext.hpp>
#endif

namespace mgl
{
	GLContext::GLContext(uint major, uint minor) :
		major(major), minor(minor) {}

	Ref<GLContext> createGLContext(const Window* window, uint major, uint minor)
	{
#ifdef _WIN32
		return CreateRef<win32::GLContext>(window, major, minor);
#endif
	}
}