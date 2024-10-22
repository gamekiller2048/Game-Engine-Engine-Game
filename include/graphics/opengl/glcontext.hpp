#pragma once
#include <graphics/rendercontext.hpp>
#include <graphics/window.hpp>

namespace mgl
{
	class GLContext : public RenderContext
	{
	public:
		GLContext(uint major, uint minor);

		virtual void useWindow(const Window* window) = 0;
		virtual void makeCurrent() = 0;
		virtual void swapBuffers() = 0;
		virtual bool isCurrent() const = 0;
		virtual bool isWindowUsed(const Window* window) const = 0;

	protected:
		uint major;
		uint minor;
	};

	Ref<GLContext> createGLContext(const Window* window, uint major, uint minor);
}