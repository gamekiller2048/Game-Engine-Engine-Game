#pragma once
#include <vector>
#include <glad/gl.h>
#include <math/math.hpp>
#include <graphics/geometry/vertex.hpp>
#include <graphics/geometry/shape2d.hpp>

namespace mgl
{
    class Shape2D
    {
    public:
        Shape2D(const mml::vec2& pos=mml::vec2(0), const mml::vec2& scale=mml::vec2(1), float rotate=0);

        mml::vec2 pos;
        mml::mat2 model;

        Geometry<Vertex2D, GLuint> Square();
        Geometry<Vertex2DUV, GLuint> SquareUV();
        Geometry<Vertex2D, GLuint> Circle();
    };
}
