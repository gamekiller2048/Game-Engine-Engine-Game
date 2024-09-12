#pragma once
#include <graphics/window.hpp>
#include <graphics/win32/devicecontext.hpp>

namespace mgl
{
	namespace win32
	{
		class WindowImpl;
		class Window : public mgl::Window
		{
		public:
			Window(const std::string& title, uint width, uint height);
			~Window();

			WindowImpl* getImpl() const;
			void destroy();
			void show();
			void hide();

			void setTitle(const std::string& title);
			void setX(int x);
			void setY(int y);
			void setPos(const mml::ivec2& pos);
			void setWidth(uint width);
			void setHeight(uint height);
			void setSize(const mml::uvec2& size);

		protected:
			Owned<WindowImpl> impl;
			DeviceContext dc;
		};
}
}