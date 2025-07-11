#include <graphics/opengl/geometryshader.hpp>

namespace mgl
{
    namespace gl
    {
        GeometryShader::GeometryShader() :
            Shader(ShaderType::GEOMETRY) {}

        GeometryShader::GeometryShader(GeometryShader&& other) noexcept :
            Shader(std::move(other)) {}
    }
}