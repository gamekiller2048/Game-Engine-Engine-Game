#include <graphics/opengl/vbo.hpp>

namespace mgl
{
    namespace gl
    {
        VBO::VBO() :
            Buffer(BufferType::VERTEX) {}

        VBO::VBO(VBO&& other) noexcept :
            Buffer(std::move(other)) {}
    }
}
