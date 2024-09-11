#pragma once
#include <vector>
#include <graphics/window.hpp>

namespace mgl
{
	class App
	{
	public:
		virtual void run() = 0;
		virtual void destroy() = 0;
		void addWindow(const Ref<Window>& window);
	
	protected:
		std::vector<Ref<Window>> windows;
	};

	Ref<App> createApp();
}