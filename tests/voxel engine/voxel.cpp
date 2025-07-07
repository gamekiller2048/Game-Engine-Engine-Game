#include "mesher.hpp"
#include <graphics/opengl/enums.hpp>

namespace VE
{
    mgl::VertexLayout BlockVertex::vertexLayout() const
    {
        return mgl::VertexLayout{
            {
                mgl::VertexLayoutAttribute{0, 3, (uint)mgl::gl::Primative::FLOAT, 3 * sizeof(GLfloat)},
                mgl::VertexLayoutAttribute{1, 3, (uint)mgl::gl::Primative::FLOAT, 2 * sizeof(GLfloat)},
                mgl::VertexLayoutAttribute{2, 3, (uint)mgl::gl::Primative::FLOAT, 3 * sizeof(GLfloat)}
            }, 8 * sizeof(GLfloat)
        };
    }

    BlockMaterial::BlockMaterial(mgl::RenderContext* context) :
        Material(context)
    {
        shader = context->createShaderProgram();
        shader->attachGLSLShadersFromSrc(
            R"(
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
uniform mat4 u_projection;
uniform mat4 u_transform;
out vec3 col;
void main()
{
    col = color;
    gl_Position = vec4(pos, 1) * u_transform * u_projection;
})",

R"(
in vec3 col;
void main()
{
	gl_FragColor = vec4(col, 1);
})"
);
    }

    void BlockMaterial::use() const
    {

    }
}