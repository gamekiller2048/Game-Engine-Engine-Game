#include <graphics/render/mesh.hpp>

namespace mgl
{
	Mesh::Mesh(RenderContext* context)
	{
		vertexBuffer = context->createVertexBuffer();
		indexBuffer = context->createIndexBuffer();
	}

	void Mesh::create()
	{
		vertexBuffer->create();
		indexBuffer->create();
	}

	void Mesh::bind()
	{
		vertexBuffer->bind();
		indexBuffer->bind();
	}

	void Mesh::draw(const Ref<ShaderProgram>& shader)
	{
		bind();
		if(indiceCount)
			shader->drawElements(indiceCount);
		else
			shader->drawArrays(0, vertexCount);
	}
}