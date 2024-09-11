#pragma once
#include <unordered_map>
#include <math/math.hpp>
#include <graphics/rendercontext.hpp>
#include <graphics/scene.hpp>

namespace mgl
{
	class Window
	{
	public:
		Window(const std::string& title, uint width, uint height, RenderApi api);
		virtual ~Window() = default;

		void addScene(const std::string& name, const Ref<Scene>& scene);
		void setScene(const std::string& name);
		Ref<Scene> getScene() const;

		void createContext();
		void setContext(const Ref<RenderContext>& context);
		Ref<RenderContext> getContext() const;

		bool isDestroyed() const;

		virtual void destroy() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;

		std::string getTitle() const;
		int getX() const;
		int getY() const;
		mml::ivec2 getPos() const;
		uint getWidth() const;
		uint getHeight() const;
		mml::uvec2 getSize() const;

		virtual void setTitle(const std::string& title) = 0;
		virtual void setX(int x) = 0;
		virtual void setY(int y) = 0;
		virtual void setPos(const mml::ivec2& pos) = 0;
		virtual void setWidth(uint width) = 0;
		virtual void setHeight(uint height) = 0;
		virtual void setSize(const mml::uvec2& size) = 0;

	protected:
		std::string title;
		mml::ivec2 pos;
		mml::uvec2 size;
		bool destroyed = false;

		RenderApi api;
		Ref<RenderContext> context;

		std::unordered_map<std::string, Ref<Scene>> scenes;
		Ref<Scene> curScene;
	};

	Ref<Window> createWindow(const std::string& title, uint width, uint height, RenderApi api);
}
