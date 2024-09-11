#include <graphics/opengl/globject.hpp>

namespace mgl
{
    GLObject::GLObject(GLenum gltype) :
        gltype(gltype) {}

    GLObject::GLObject(GLObject&& other) noexcept
    {
        gltype = other.gltype;
        id = other.id;
        other.id = 0;
    }

    GLuint GLObject::getID() const
    {
        return id;
    }

    GLenum GLObject::getGLType() const
    {
        return gltype;
    }
}