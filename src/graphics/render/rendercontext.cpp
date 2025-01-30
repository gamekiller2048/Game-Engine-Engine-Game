#include <graphics/render/rendercontext.hpp>
#include <graphics/render/mesh.hpp>

namespace mgl
{
	Ref<Mesh> RenderContext::createMesh()
	{
		return CreateRef<Mesh>(this);
	}
}