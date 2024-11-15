#pragma once
#include <vector>
#include <unordered_map>
#include <math/math.hpp>
#include <graphics/scene.hpp>
#include <graphics/rendercontext.hpp>

namespace mgl
{
	// TODO: implement the hints
	enum class WindowHint
	{
		FULLSCREEN,
		BORDERLESS,
		MINIMIZABLE
	};

	class WindowImpl;
	class Window
	{
	public:
		Window(const std::string& title, uint width, uint height, const std::vector<WindowHint>& hints = {});
		~Window();

		WindowImpl* getImpl() const;

		void create();
		void addScene(const std::string& name, const Ref<Scene>& scene);
		void setScene(const std::string& name);
		Ref<Scene> getScene() const;

		void setContext(const Ref<RenderContext>& context);
		Ref<RenderContext> getContext() const;

		bool isDestroyed() const;
		void preventDefaultCallback();

		void destroy();
		void show();
		void hide();

		std::string getTitle() const;
		int getX() const;
		int getY() const;
		mml::ivec2 getPos() const;
		uint getWidth() const;
		uint getHeight() const;
		mml::uvec2 getSize() const;

		void setTitle(const std::string& title);
		void setX(int x);
		void setY(int y);
		void setPos(const mml::ivec2& pos);
		void setWidth(uint width);
		void setHeight(uint height);
		void setSize(const mml::uvec2& size);

		mml::vec2 getMousePos() const;
		void setMousePos(const mml::ivec2 & pos) const;

		bool defaultCallback = true;

	protected:
		Owned<WindowImpl> impl;
		friend class WindowImpl;

		std::string title;
		mml::ivec2 pos;
		mml::uvec2 size;
		bool destroyed = false;

		Ref<RenderContext> context;

		std::unordered_map<std::string, Ref<Scene>> scenes;
		Ref<Scene> curScene;
	};
}