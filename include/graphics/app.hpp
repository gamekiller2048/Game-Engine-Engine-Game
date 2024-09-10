#pragma once
#include <graphics/window.hpp>
#include <vector>

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