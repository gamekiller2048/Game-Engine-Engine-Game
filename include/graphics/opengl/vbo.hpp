#pragma once
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    namespace gl
    {
        class VBO : public Buffer
        {
        public:
            VBO();
            VBO(VBO&& other) noexcept;
        };
    }
}
