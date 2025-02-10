#include <graphics/geometry/util.hpp>

namespace mgl
{
	void calculateFlatNormals(Geometry<gl::Vertex3DUVN, GLuint>& geometry)
	{
		for(int i = 0; i < geometry.indices.size() - 2; i += 3) {
			mml::vec3 v1 = geometry.vertices[geometry.indices[i + 1]].pos - geometry.vertices[geometry.indices[i]].pos;
			mml::vec3 v2 = geometry.vertices[geometry.indices[i + 2]].pos - geometry.vertices[geometry.indices[i]].pos;

			GLvec3 normal = (GLvec3)v1.cross(v2).normalize();
			geometry.vertices[geometry.indices[i]].normal = normal;
			geometry.vertices[geometry.indices[i + 1]].normal = normal;
			geometry.vertices[geometry.indices[i + 2]].normal = normal;
		}
	}

	void calculateSmoothNormals(Geometry<gl::Vertex3DUVN, GLuint>& geometry)
	{
		for(int i = 0; i < geometry.indices.size() - 2; i += 3) {
			mml::vec3 v1 = geometry.vertices[geometry.indices[i + 1]].pos - geometry.vertices[geometry.indices[i]].pos;
			mml::vec3 v2 = geometry.vertices[geometry.indices[i + 2]].pos - geometry.vertices[geometry.indices[i]].pos;

			GLvec3 normal = (GLvec3)v1.cross(v2);
			geometry.vertices[geometry.indices[i]].normal += normal;
			geometry.vertices[geometry.indices[i + 1]].normal += normal;
			geometry.vertices[geometry.indices[i + 2]].normal += normal;
		}

		for(gl::Vertex3DUVN& vertex : geometry.vertices)
			vertex.normal = (vertex.normal / 3.0f).normalize();
	}
}