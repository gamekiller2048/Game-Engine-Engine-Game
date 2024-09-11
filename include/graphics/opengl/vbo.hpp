#pragma once
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    class VBO : public Buffer
    {
    public:
        VBO();
        VBO(VBO&& other) noexcept;
    };
}
