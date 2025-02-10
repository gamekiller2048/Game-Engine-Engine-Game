#include <graphics/render/model.hpp>
#include <math/transform.hpp>

namespace mgl
{
	Ref<Mesh> Model::getMesh() const
	{
		return mesh;
	}

	Ref<Material> Model::getMaterial() const
	{
		return material;
	}

	mml::vec3 Model::getPos() const
	{
		return pos;
	}

	mml::vec3 Model::getRotate() const
	{
		return rotate;
	}

	mml::vec3 Model::getScale() const
	{
		return scale;
	}

	mml::mat4 Model::getTransform() const
	{
		return transform;
	}

	void Model::setMesh(const Ref<Mesh>& mesh)
	{
		this->mesh = mesh;
	}

	void Model::setMaterial(const Ref<Material>& material)
	{
		this->material = material;
	}

	mml::mat4 Model::calculateTransform()
	{
		return mml::translate(mml::rotate(mml::scale(mml::mat4(1), scale), rotate), pos);
	}

	void Model::setPos(const mml::vec3& pos)
	{
		this->pos = pos;
		setTransform(calculateTransform());
	}

	void Model::setRotate(const mml::vec3& rotate)
	{
		this->rotate = rotate;
		setTransform(calculateTransform());
	}

	void Model::setScale(const mml::vec3& scale)
	{
		this->scale = scale;
		setTransform(calculateTransform());
	}

	void Model::setTransform(const mml::mat4& transform)
	{
		this->transform = transform;
	}
}