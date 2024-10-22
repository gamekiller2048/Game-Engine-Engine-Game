// TODO: interface for each api (currently only openGL)
#pragma once
#include <vector>
#include <math/math.hpp>
#include <graphics/opengl/buffer.hpp>
#include <graphics/opengl/gltypes.hpp>

namespace mgl
{
    namespace gl
    {
        template<typename T, typename U>
        struct Geometry
        {
            std::vector<T> vertices;
            std::vector<U> indices;
        };

        struct Vertex2D
        {
            GLvec2 pos;

            std::vector<VBI> structure() const;
        };

        struct Vertex2DUV
        {
            GLvec2 pos;
            GLvec2 texUV;

            std::vector<VBI> structure() const;
        };


        struct Vertex3D
        {
            GLvec3 pos;

            std::vector<VBI> structure() const;
        };

        struct Vertex3DUV
        {
            GLvec3 pos;
            GLvec2 texUV;

            std::vector<VBI> structure() const;
        };

        struct Vertex3DN
        {
            GLvec3 pos;
            GLvec3 normal;

            std::vector<VBI> structure() const;
        };

        struct Vertex3DUVN
        {
            GLvec3 pos;
            GLvec2 texUV;
            GLvec3 normal;

            std::vector<VBI> structure() const;
        };
    }
}
