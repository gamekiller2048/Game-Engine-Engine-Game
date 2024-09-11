#pragma once
#include <glad/gl.h>

namespace mgl
{
    enum class Access : GLuint
    {
        READ_ONLY = GL_READ_ONLY,
        WRITE_ONLY = GL_WRITE_ONLY,
        READ_WRITE = GL_READ_WRITE
    };

    enum class Primative : GLuint
    {
        FLOAT = GL_FLOAT,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        SHORT = GL_SHORT,
        USHORT = GL_UNSIGNED_SHORT,
        BYTE = GL_BYTE,
        UBYTE = GL_UNSIGNED_BYTE,
        BOOL = GL_BOOL,
        DOUBLE = GL_DOUBLE
    };

    enum class RenderPrimative : GLuint
    {
        POINTS = GL_POINTS,
        LINE_STRIP = GL_LINE_STRIP,
        LINE_LOOP = GL_LINE_LOOP,
        LINES = GL_LINES,
        LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
        LINES_ADJACENCY = GL_LINES_ADJACENCY,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        TRIANGLE_FAN = GL_TRIANGLE_FAN,
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
        PATCHES = GL_PATCHES
    };

    enum class DrawMode : GLuint
    {
        FILL=GL_FILL,
        POINT=GL_POINT,
        LINE=GL_LINE
    };

    enum class DepthFunc : GLuint
    {
        NEVER = GL_NEVER,
        LESS = GL_LESS,
        EQUAL = GL_EQUAL,
        LEQUAL = GL_LEQUAL,
        GREATER = GL_GREATER,
        NOTEQUAL = GL_NOTEQUAL,
        GEQUAL = GL_GEQUAL,
        ALWAYS = GL_ALWAYS
    };

    enum class TransparentFunc : GLuint
    {
        SRC_COLOR = GL_SRC_COLOR,
        ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        SRC_ALPHA = GL_SRC_ALPHA,
        ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
    };

    enum class FaceSide : GLuint
    {
        FRONT_LEFT = GL_FRONT_LEFT,
        FRONT_RIGHT = GL_FRONT_RIGHT,
        BACK_LEFT = GL_BACK_LEFT,
        BACK_RIGHT = GL_BACK_RIGHT,
        FRONT = GL_FRONT,
        BACK = GL_BACK,
        LEFT = GL_LEFT,
        RIGHT = GL_RIGHT,
        FRONT_AND_BACK = GL_FRONT_AND_BACK
    };
}
