#include <graphics/opengl/ebo.hpp>

namespace mgl
{
    namespace gl
    {
        EBO::EBO() :
            Buffer(BufferType::ELEMENT) {}

        EBO::EBO(EBO&& other) noexcept :
            Buffer(std::move(other)) {}
    }
}
