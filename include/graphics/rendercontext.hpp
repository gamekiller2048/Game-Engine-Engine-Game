#pragma once

namespace mgl
{
	enum class RenderApi {
		OPENGL
	};

	class Window;
	class RenderContext
	{
	public:
		RenderContext() = default;
		virtual ~RenderContext() = default;
		
		virtual void useWindow(const Window* window) = 0;
		virtual void makeCurrent() = 0;
		virtual void swapBuffers() = 0;
		virtual bool isCurrent() const = 0;
		virtual bool isWindowUsed(const Window* window) const = 0;
	};
}