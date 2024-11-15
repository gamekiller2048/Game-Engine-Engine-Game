#include <vector>
#include <graphics/render/mesh.hpp>

namespace mgl
{
	class RenderScene
	{
	public:
		void addMesh(const Ref<Mesh>& mesh);
	
	protected:
		std::vector<Ref<Mesh>> meshes;
	};
}