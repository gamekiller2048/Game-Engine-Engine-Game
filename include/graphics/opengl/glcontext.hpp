#pragma once
#include <graphics/rendercontext.hpp>
#include <graphics/window.hpp>

namespace mgl
{
	enum class GLContextProfile
	{
		CORE,
		COMPATABILITY
	};

	class GLContextImpl;
	class GLContext : public RenderContext
	{
	public:
		GLContext(Window* window, uint major, uint minor, GLContextProfile profile = GLContextProfile::CORE);
		~GLContext();

		void create(Window* window);
		void useWindow(const Window* window);
		void makeCurrent();
		void swapBuffers();
		bool isCurrent() const;
		bool isWindowUsed(const Window* window) const ;

	protected:
		Owned<GLContextImpl> impl;

		uint major;
		uint minor;
		GLContextProfile profile;
	};
}