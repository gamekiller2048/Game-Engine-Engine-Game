#pragma once
#include <glad/gl.h>
#include <unordered_set>
#include <graphics/opengl/globject.hpp>
#include <graphics/opengl/enums.hpp>
#include <logging/logging.hpp>
#include <graphics/errors.hpp>

namespace mgl
{
    namespace gl
    {
        enum class TextureParam : GLuint
        {
            MAG_FILTER = GL_TEXTURE_MAG_FILTER,
            MIN_FILTER = GL_TEXTURE_MIN_FILTER,
            WRAP_S = GL_TEXTURE_WRAP_S,
            WRAP_T = GL_TEXTURE_WRAP_T,
            INTERNAL_FORMAT = GL_TEXTURE_INTERNAL_FORMAT,
            RED_SIZE = GL_TEXTURE_RED_SIZE,
            GREEN_SIZE = GL_TEXTURE_GREEN_SIZE,
            BLUE_SIZE = GL_TEXTURE_BLUE_SIZE,
            ALPHA_SIZE = GL_TEXTURE_ALPHA_SIZE,
            DEPTH = GL_TEXTURE_DEPTH,
            WRAP_R = GL_TEXTURE_WRAP_R,
            MIN_LOD = GL_TEXTURE_MIN_LOD,
            MAX_LOD = GL_TEXTURE_MAX_LOD,
            BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
            MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
            LOD_BIAS = GL_TEXTURE_LOD_BIAS,
            COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
            COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
            VIEW_MIN_LEVEL = GL_TEXTURE_VIEW_MIN_LEVEL,
            VIEW_NUM_LEVELS = GL_TEXTURE_VIEW_NUM_LEVELS,
            VIEW_MIN_LAYER = GL_TEXTURE_VIEW_MIN_LAYER,
            VIEW_NUM_LAYERS = GL_TEXTURE_VIEW_NUM_LAYERS,
            IMMUTABLE_LEVELS = GL_TEXTURE_IMMUTABLE_LEVELS,
            BORDER_COLOR = GL_TEXTURE_BORDER_COLOR
        };

        enum class TextureLevelParam : GLuint
        {
            WIDTH = GL_TEXTURE_WIDTH,
            HEIGHT = GL_TEXTURE_HEIGHT,
            DEPTH = GL_TEXTURE_DEPTH,
            INTERNAL_FORMAT = GL_TEXTURE_INTERNAL_FORMAT,
            RED_SIZE = GL_TEXTURE_RED_SIZE,
            GREEN_SIZE = GL_TEXTURE_GREEN_SIZE,
            BLUE_SIZE = GL_TEXTURE_BLUE_SIZE,
            ALPHA_SIZE = GL_TEXTURE_ALPHA_SIZE,
            COMPRESSED_IMAGE_SIZE = GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
            COMPRESSED = GL_TEXTURE_COMPRESSED,
            RED_TYPE = GL_TEXTURE_RED_TYPE,
            GREEN_TYPE = GL_TEXTURE_GREEN_TYPE,
            BLUE_TYPE = GL_TEXTURE_BLUE_TYPE,
            ALPHA_TYPE = GL_TEXTURE_ALPHA_TYPE,
            DEPTH_TYPE = GL_TEXTURE_DEPTH_TYPE,
            BUFFER_OFFSET = GL_TEXTURE_BUFFER_OFFSET,
            BUFFER_SIZE = GL_TEXTURE_BUFFER_SIZE
        };

        enum class Format : GLuint
        {
            RED_INTEGER = GL_RED_INTEGER,
            R8 = GL_R8,
            R8UI = GL_R8UI,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA,
            BGR = GL_BGR,
            BGRA = GL_BGRA,
            RED = GL_RED,
            GREEN = GL_GREEN,
            BLUE = GL_BLUE,
            ALPHA = GL_ALPHA,
            RGB4 = GL_RGB4,
            RGB5 = GL_RGB5,
            RGB8 = GL_RGB8,
            RGB8UI = GL_RGB8UI,
            RGB10 = GL_RGB10,
            RGB12 = GL_RGB12,
            RGB16 = GL_RGB16,
            RGB_INTEGER = GL_RGB_INTEGER,
            RGBA2 = GL_RGBA2,
            RGBA4 = GL_RGBA4,
            RGB5_A1 = GL_RGB5_A1,
            RGBA8 = GL_RGBA8,
            RGB10_A2 = GL_RGB10_A2,
            RGBA12 = GL_RGBA12,
            RGBA8UI = GL_RGBA8UI,
            RGBA_INTEGER = GL_RGBA_INTEGER,
            RGBA16 = GL_RGBA16,
            RGBA32F = GL_RGBA32F,
            DEPTH = GL_DEPTH_COMPONENT,
            DEPTH16 = GL_DEPTH_COMPONENT16,
            DEPTH24 = GL_DEPTH_COMPONENT24,
            DEPTH32 = GL_DEPTH_COMPONENT32,
            DEPTH32F = GL_DEPTH_COMPONENT32F
        };

        enum class TexFilter : GLuint
        {
            NEAREST = GL_NEAREST,
            LINEAR = GL_LINEAR,
            MIPMAP_NEAREST_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
            MIPMAP_LINEAR_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
            MIPMAP_NEAREST_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
            MIPMAP_LINEAR_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
            REPEAT = GL_REPEAT,
            MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
            CLAMP_EDGE = GL_CLAMP_TO_EDGE
        };

        struct TexFilterOptions
        {
            TexFilter min = TexFilter::NEAREST;
            TexFilter mag = TexFilter::NEAREST;
            TexFilter wrapS = TexFilter::REPEAT;
            TexFilter wrapT = TexFilter::REPEAT;
            TexFilter wrapR = TexFilter::REPEAT;
        };

        class Texture : public GLObject
        {
        public:
            Texture(GLenum gltype);
            Texture(Texture&& other) noexcept;
            ~Texture();

            void create();
            void bind() const;
            void setActiveUnit() const;
            void bindImage(GLuint imgUnit, GLuint level, Access access, GLint layer=-1) const;
            void unbind() const;

            GLint getParameterInt(TextureParam param) const;
            GLfloat getParameterFloat(TextureParam param) const;

            GLint getLevelParameterInt(TextureLevelParam param, GLuint level=0) const;
            GLfloat getLevelParameterFloat(TextureLevelParam param, GLuint level = 0) const;

            template<typename T>
            void setParameter(TextureParam param, T value);

            GLuint getUnit() const;
            Primative getPixelType() const;
            Format getFormat() const;
            TexFilterOptions getTexFilters() const;

            void read(void* data, GLuint mipMapReduction=0) const;
            void setTexFilters(const TexFilterOptions& filters);
            void setUnit(GLuint unit);

        protected:
            GLuint unit = -1;
            Primative pixelType;
            Format format;
            Format internalFormat;
            TexFilterOptions filters;
        };
    }
}
