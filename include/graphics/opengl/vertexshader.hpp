#pragma once
#include <graphics/opengl/shader.hpp>

namespace mgl
{
	namespace gl
	{
		class VertexShader : public Shader
		{
		public:
			VertexShader();
			VertexShader(VertexShader&& other) noexcept;
		};
	}
}