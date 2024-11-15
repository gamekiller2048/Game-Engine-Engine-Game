#include <graphics/render/shadow.hpp>
#include <graphics/render/modelmesh.hpp>

namespace mgl
{
	Shadow::Shadow(float bias, int sampleRadius) :
		bias(bias), sampleRadius(sampleRadius) {}

	void Shadow::useMeshTransform(const Ref<ModelMesh>& mesh)
	{
		shader.uniformMat4("u_model", mesh->getTransform());
	}
}