#include <graphics/opengl/ebo.hpp>

namespace mgl
{
    EBO::EBO() :
        Buffer(BufferType::ELEMENT) {}

    EBO::EBO(EBO&& other) noexcept :
        Buffer(std::move(other)) {}
}
