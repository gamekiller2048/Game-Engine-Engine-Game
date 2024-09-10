#pragma once
#include <graphics/opengl/glcontext.hpp>
#include <graphics/win32/devicecontext.hpp>

namespace mgl
{
	namespace win32
	{
		class GLContextImpl;
		class GLContext : public mgl::GLContext
		{
		public:
			GLContext(const mgl::Window* window, uint major, uint minor);
			~GLContext();

			void useWindow(const mgl::Window* window);
			void releaseWindow(const mgl::Window* window);
			void makeCurrent();
			void swapBuffers();
			bool isCurrent() const;

		protected:
			Owned<GLContextImpl> impl;
		};
	}
}