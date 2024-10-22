#include <graphics/opengl/vertexshader.hpp>

namespace mgl
{
	namespace gl
	{
		VertexShader::VertexShader() :
			Shader(ShaderType::VERTEX) {}

		VertexShader::VertexShader(VertexShader&& other) noexcept :
			Shader(std::move(other)) {}
	}
}