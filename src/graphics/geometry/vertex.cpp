#include <graphics/geometry/vertex.hpp>

namespace mgl
{
    namespace gl
    {
        std::vector<VBI> Vertex2D::structure() const {return {VBI{0, 2, Primative::FLOAT}};}
        std::vector<VBI> Vertex2DUV::structure() const {return {VBI{0, 2, Primative::FLOAT}, VBI{1, 2, Primative::FLOAT}};}
        std::vector<VBI> Vertex3D::structure() const {return {VBI{0, 3, Primative::FLOAT}};}
        std::vector<VBI> Vertex3DUV::structure() const {return {VBI{0, 3, Primative::FLOAT}, VBI{1, 2, Primative::FLOAT}};}
        std::vector<VBI> Vertex3DN::structure() const {return {VBI{0, 3, Primative::FLOAT}, VBI{1, 3, Primative::FLOAT}};}
        std::vector<VBI> Vertex3DUVN::structure() const {return {VBI{0, 3, Primative::FLOAT}, VBI{1, 2, Primative::FLOAT}, VBI{2, 3, Primative::FLOAT}};}
    }
}

