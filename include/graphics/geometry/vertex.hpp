#pragma once
#include <math/math.hpp>
#include <vector>
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    template<typename T, typename U>
    struct Geometry
    {
        std::vector<T> vertices;
        std::vector<U> indices;
    };

    struct Vertex2D
    {
        mml::vec2 pos;

        std::vector<VBI> structure() const;
    };

    struct Vertex2DUV
    {
        mml::vec2 pos;
        mml::vec2 texUV;

        std::vector<VBI> structure() const;
    };


    struct Vertex3D
    {
        mml::vec3 pos;

        std::vector<VBI> structure() const;
    };

    struct Vertex3DUV
    {
        mml::vec3 pos;
        mml::vec2 texUV;

        std::vector<VBI> structure() const;
    };

    struct Vertex3DN
    {
        mml::vec3 pos;
        mml::vec3 normal;

        std::vector<VBI> structure() const;
    };

    struct Vertex3DUVN
    {
        mml::vec3 pos;
        mml::vec2 texUV;
        mml::vec3 normal;

        std::vector<VBI> structure() const;
    };
}
