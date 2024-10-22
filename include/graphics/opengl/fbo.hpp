#pragma once
#include <glad/gl.h>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/texture2d.hpp>
#include <graphics/opengl/rbo.hpp>

namespace mgl
{
    namespace gl
    {
        enum class BufferBit : GLuint
        {
            COLOR = GL_COLOR_BUFFER_BIT,
            DEPTH = GL_DEPTH_BUFFER_BIT,
            STENCIL = GL_STENCIL_BUFFER_BIT
        };

        enum class Attachment : GLuint
        {
            COLOR = GL_COLOR_ATTACHMENT0,
            DEPTH = GL_DEPTH_ATTACHMENT
        };

        class FBO : public GLObject
        {
        public:
            FBO();
            FBO(FBO&& other) noexcept;
            ~FBO();
        
            void create();
            void bind() const;
            void unbind() const;

            void clear(BufferBit bufferbit) const;
            void viewport(GLuint x, GLuint y, GLuint w, GLuint h) const;
            void read(void* data, Format format, Primative pixelType, const mml::ivec4& bounds) const;
            void attachTexture(const Texture& texture, Attachment attachment, int attachmentIndex=0) const;
            void attachRBO(const RBO& rbo, Attachment attachment, int attachmentIndex=0) const;
            void setDrawAttachments(const std::vector<GLenum>& attachments) const;
            void setReadAttachment(GLenum attachment) const;
        };
    }
}
