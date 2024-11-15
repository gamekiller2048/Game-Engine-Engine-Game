#include <graphics/render/mesh.hpp>
#include <graphics/app.hpp>
#include <graphics/render/opengl/mesh.hpp>

namespace mgl
{
	Ref<Mesh> createMesh()
	{
		switch(App::getInstance()->getRenderApi()) {
		case RenderApi::OPENGL:
			return CreateRef<gl::Mesh>();
		}

		return nullptr;
	}
}