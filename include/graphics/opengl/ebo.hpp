#pragma once
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    namespace gl
    {
        class EBO : public Buffer
        {
        public:
            EBO();
            EBO(EBO&& other) noexcept;
        };
    }
}
