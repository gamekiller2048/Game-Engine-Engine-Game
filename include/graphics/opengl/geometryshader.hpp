#pragma once
#include <graphics/opengl/shader.hpp>

namespace mgl
{
	class GeometryShader : public Shader
	{
	public:
		GeometryShader();
		GeometryShader(GeometryShader&& other) noexcept;
	};
}