#pragma once
#include <graphics/opengl/shader.hpp>

namespace mgl
{
	namespace gl
	{
		class FragmentShader : public Shader
		{
		public:
			FragmentShader();
			FragmentShader(FragmentShader&& other) noexcept;
		};
	}
}