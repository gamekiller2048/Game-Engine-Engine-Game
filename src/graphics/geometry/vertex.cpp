#include <graphics/geometry/vertex.hpp>
#include <graphics/opengl/buffer.hpp>

namespace mgl
{
    namespace gl
    {
        VertexLayout Vertex2D::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 2, (uint)Primative::FLOAT, 2 * sizeof(GLfloat)}}, 2 * sizeof(GLfloat)};}
        VertexLayout Vertex2DUV::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 2, (uint)Primative::FLOAT, 2 * sizeof(GLfloat)}, VertexLayoutAttribute{1, 2, (uint)Primative::FLOAT, 2 * sizeof(GLfloat)}}, 4 * sizeof(GLfloat)};}
        VertexLayout Vertex3D::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}}, 3 * sizeof(GLfloat)};}
        VertexLayout Vertex3DUV::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}, VertexLayoutAttribute{1, 2, (uint)Primative::FLOAT, 2 * sizeof(GLfloat)}}, 5 * sizeof(GLfloat)};}
        VertexLayout Vertex3DN::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}, VertexLayoutAttribute{1, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}}, 6 * sizeof(GLfloat)};}
        VertexLayout Vertex3DUVN::vertexLayout() const {return VertexLayout{{VertexLayoutAttribute{0, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}, VertexLayoutAttribute{1, 2, (uint)Primative::FLOAT, 2 * sizeof(GLfloat)}, VertexLayoutAttribute{2, 3, (uint)Primative::FLOAT, 3 * sizeof(GLfloat)}}, 8 * sizeof(GLfloat)};}
    }
}

