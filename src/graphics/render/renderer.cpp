#include <graphics/render/renderer.hpp>
#include <graphics/app.hpp>
#include <graphics/render/opengl/renderer.hpp>

namespace mgl
{
	Ref<Renderer> createRenderer()
	{
		switch(App::getInstance()->getRenderApi()) {
		case RenderApi::OPENGL:
			return CreateRef<gl::Renderer>();
		}

		return nullptr;
	}
}