#include <graphics/renderer.hpp>
#include <graphics/app.hpp>

namespace mgl
{
	Ref<Renderer> createRenderer()
	{
		switch(App::getInstance()->getRenderApi()) {
		case RenderApi::OPENGL:
			return 
		}
	}
}