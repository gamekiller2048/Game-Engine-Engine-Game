#include <graphics/opengl/texture.hpp>
#include <iterator>
#include <numeric>
#include <graphics/opengl/shader.hpp>
#include <graphics/opengl/enums.hpp>
#include <graphics/opengl/context.hpp>
#include "errorcheck.hpp"

namespace mgl
{
    namespace gl
    {
        Texture::Texture(GLenum gltype) :
            GLObject(gltype)
        {
            this->gltype = gltype;
        }

        Texture::Texture(Texture&& other) noexcept :
            GLObject(std::move(other))
        {
            format = other.format;
            internalFormat = other.internalFormat;
            pixelType = other.pixelType;
            unit = other.unit;
        }

        Texture::~Texture()
        {
            GL_CALL(glDeleteTextures, 1, &id);
        }

        void Texture::create()
        {
            GL_CALL(glGenTextures, 1, &id);
        }

        // note: this actually binds the texture to the active unit (glActiveTexture)
        // so if the texture needs to be bound for operations but keeping unit, you should call setActiveUnit
        void Texture::bind() const
        {
            GL_CALL(glBindTexture, gltype, id);
            unit = Context::getCurrent()->getParameterInt(mgl::gl::ContextParam::ACTIVE_TEXTURE);
        }

        void Texture::setActiveUnit() const
        {
            GL_CALL(glActiveTexture, GL_TEXTURE0 + unit);
            GL_CALL(glBindTexture, gltype, id);
        }

        void Texture::bindImage(GLuint imgUnit, GLuint level, Access access, GLint layer) const
        {
            GL_CALL(glBindImageTexture, imgUnit, id, level, layer != -1, layer == -1 ? 0 : layer, (GLenum)access, (GLenum)internalFormat);
        }

        void Texture::unbind() const
        {
            GL_CALL(glBindTexture, gltype, 0);
        }

        GLint Texture::getParameterInt(TextureParam param) const
        {
            GLint result;
            GL_CALL(glGetTexParameteriv, id, (GLenum)param, &result);
            return result;
        }

        GLfloat Texture::getParameterFloat(TextureParam param) const
        {
            GLfloat result;
            GL_CALL(glGetTexParameterfv, id, (GLenum)param, &result);
            return result;
        }

        GLint Texture::getLevelParameterInt(TextureLevelParam param, GLuint level) const
        {
            GLint result;
            GL_CALL(glGetTexLevelParameteriv, id, (GLenum)param, level, &result);
            return result;
        }

        GLfloat Texture::getLevelParameterFloat(TextureLevelParam param, GLuint level) const
        {
            GLfloat result;
            GL_CALL(glGetTexLevelParameterfv, id, (GLenum)param, level, &result);
            return result;
        }

        GLuint Texture::getUnit() const
        {
            return unit;
        }

        Primative Texture::getPixelType() const
        {
            return pixelType;
        }

        Format Texture::getFormat() const
        {
            return format;
        }

        TexFilterOptions Texture::getTexFilters() const
        {
            return filters;
        }

        void Texture::read(void* data, GLuint mipMapReduction) const
        {
            GL_CALL(glGetTexImage, gltype, mipMapReduction, (GLenum)format, (GLenum)pixelType, data);
        }

        template<>
        void Texture::setParameter(TextureParam param, GLint value)
        {
            GL_CALL(glTexParameteri, gltype, (GLenum)param, value);
        }

        template<>
        void Texture::setParameter(TextureParam param, GLfloat value)
        {
            GL_CALL(glTexParameterf, gltype, (GLenum)param, value);
        }

        void Texture::setTexFilters(const TexFilterOptions& filters)
        {
            setParameter(TextureParam::MIN_FILTER, (GLint)filters.min);
            setParameter(TextureParam::MAG_FILTER, (GLint)filters.mag);
            setParameter(TextureParam::WRAP_S, (GLint)filters.wrapS);
            setParameter(TextureParam::WRAP_T, (GLint)filters.wrapT);
        }

        void Texture::setUnit(GLuint unit)
        {
            this->unit = unit;
        }
    }
}
