#pragma once
#include <glad/gl.h>

namespace mgl
{
    class GLObject
    {
    public:
        GLObject(GLenum type = GL_NONE);
        GLObject(GLObject&& other) noexcept;

        GLuint getID() const;
        GLenum getGLType() const;

    protected:
        GLenum gltype;
        GLuint id = 0;
    };
}