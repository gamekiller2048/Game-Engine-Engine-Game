#pragma once
#include <vector>
#include <graphics/window.hpp>
#include <graphics/rendercontext.hpp>

namespace mgl
{
	class App
	{
	public:
		App(RenderApi api);

		virtual void run() = 0;
		virtual void destroy() = 0;
		void addWindow(const Ref<Window>& window);

		RenderApi getRenderApi() const;
		void setRenderApi(RenderApi api);
		
		static App* getInstance();

	protected:
		std::vector<Ref<Window>> windows;
		RenderApi api;

		inline static App* instance;
	};

	Ref<App> createApp(RenderApi api);
}