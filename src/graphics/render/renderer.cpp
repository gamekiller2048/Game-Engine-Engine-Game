#include <graphics/render/renderer.hpp>
#include <graphics/app.hpp>
#include <graphics/render/opengl/glrenderer.hpp>

namespace mgl
{
	Ref<Renderer> createRenderer()
	{
		switch(App::getInstance()->getRenderApi()) {
		case RenderApi::OPENGL:
			return CreateRef<GLRenderer>();
		}

		return nullptr;
	}
}