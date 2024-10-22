#pragma once
#include <graphics/opengl/shader.hpp>

namespace mgl
{
	namespace gl
	{
		class GeometryShader : public Shader
		{
		public:
			GeometryShader();
			GeometryShader(GeometryShader&& other) noexcept;
		};
	}
}