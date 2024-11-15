// TODO: interface for each api (currently only openGL)
#pragma once
#include <vector>
#include <math/math.hpp>
#include <graphics/render/vertexlayout.hpp>
#include <graphics/opengl/gltypes.hpp>

namespace mgl
{
    template<typename T, typename U>
    struct Geometry
    {
        std::vector<T> vertices;
        std::vector<U> indices;
    };

    namespace gl
    {
        struct Vertex2D
        {
            GLvec2 pos;

            VertexLayout vertexLayout() const;
        };

        struct Vertex2DUV
        {
            GLvec2 pos;
            GLvec2 texUV;

            VertexLayout vertexLayout() const;
        };


        struct Vertex3D
        {
            GLvec3 pos;

            VertexLayout vertexLayout() const;
        };

        struct Vertex3DUV
        {
            GLvec3 pos;
            GLvec2 texUV;

            VertexLayout vertexLayout() const;
        };

        struct Vertex3DN
        {
            GLvec3 pos;
            GLvec3 normal;

            VertexLayout vertexLayout() const;
        };

        struct Vertex3DUVN
        {
            GLvec3 pos;
            GLvec2 texUV;
            GLvec3 normal;

            VertexLayout vertexLayout() const;
        };
    }
}
