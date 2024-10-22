#include <graphics/opengl/rbo.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        RBO::RBO() :
            GLObject(GL_RENDERBUFFER) {}

        RBO::RBO(RBO&& other) noexcept :
            GLObject(std::move(other)) {}

        RBO::~RBO()
        {
            GL_CALL(glDeleteRenderbuffers, 1, &id);
        }

        void RBO::create()
        {
            GL_CALL(glGenRenderbuffers, 1, &id);
        }

        void RBO::bind() const
        {
            GL_CALL(glBindRenderbuffer, gltype, id);
        }

        void RBO::unbind() const
        {
            GL_CALL(glBindRenderbuffer, gltype, 0);
        }

        void RBO::allocate(GLuint width, GLuint height, Format format) const
        {
            bind();
            GL_CALL(glRenderbufferStorage, gltype, (GLenum)format, width, height);
        }
    }
}
