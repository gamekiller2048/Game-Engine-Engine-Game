#pragma once
#include <graphics/geometry/vertex.hpp>

namespace mgl
{
	void calculateFlatNormals(Geometry<gl::Vertex3DUVN, GLuint>& geometry);
	void calculateSmoothNormals(Geometry<gl::Vertex3DUVN, GLuint>& geometry);
}