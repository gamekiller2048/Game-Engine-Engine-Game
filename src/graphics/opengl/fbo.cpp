#include <graphics/opengl/fbo.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        FBO::FBO() :
            GLObject(GL_FRAMEBUFFER) {}

        FBO::FBO(FBO&& other) noexcept :
            GLObject(std::move(other)) {}

        FBO::~FBO()
        {
            GL_CALL(glDeleteFramebuffers, 1, &id);
        }

        void FBO::create()
        {
            GL_CALL(glGenFramebuffers, 1, &id);
            if(glCheckFramebufferStatus(gltype) != GL_FRAMEBUFFER_COMPLETE)
                MLL_DEBUG(GLError("failed to create framebuffer"));
        }

        void FBO::bind() const
        {
            GL_CALL(glBindFramebuffer, gltype, id);
        }

        void FBO::unbind() const
        {
            GL_CALL(glBindFramebuffer, gltype, 0);
        }

        void FBO::viewport(GLuint x, GLuint y, GLuint w, GLuint h) const
        {
            GL_CALL(glViewport, x, y, w, h);
        }

        void FBO::clear(BufferBit bufferbit) const
        {
            GL_CALL(glClear, (GLenum)bufferbit);
        }

        void FBO::read(void* data, Format format, Primative pixelgltype, const mml::ivec4& bounds) const
        {
            GL_CALL(glReadPixels, bounds.x, bounds.y, bounds.z, bounds.w, (GLenum)format, (GLenum)pixelgltype, data);
        }

        void FBO::attachTexture(const Texture& texture, Attachment attachment, int attachmentIndex) const
        {
            GL_CALL(glFramebufferTexture, gltype, (GLenum)attachment + attachmentIndex, texture.getID(), 0);
        }

        void FBO::attachRBO(const RBO& rbo, Attachment attachment, int attachmentIndex) const
        {
            GL_CALL(glFramebufferRenderbuffer, gltype, (GLenum)attachment + attachmentIndex, rbo.getGLType(), rbo.getID());
        }

        void FBO::setDrawAttachments(const std::vector<GLenum>& attachments) const
        {
            GL_CALL(glDrawBuffers, attachments.size(), attachments.data());
        }

        void FBO::setReadAttachment(GLenum attachment) const
        {
            GL_CALL(glReadBuffer, attachment);
        }
    }
}
