#pragma once
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    class EBO : public Buffer
    {
    public:
        EBO();
        EBO(EBO&& other) noexcept;
    };
}
