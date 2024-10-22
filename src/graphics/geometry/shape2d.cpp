#include <graphics/geometry/shape2d.hpp>
#include <math/math.hpp>
#include <math/transform.hpp>

namespace mgl
{
    namespace gl
    {
        Shape2D::Shape2D(const mml::vec2& pos, const mml::vec2& scale, float rotate) :
            pos(pos)
        {
            model = mml::rotate(mml::scale(mml::mat2(1), scale), rotate);
        }

        Geometry<Vertex2D, GLuint> Shape2D::Square()
        {
            std::vector<Vertex2D> vertices = {
                Vertex2D {mml::vec2(-1, 1) * model + pos},
                Vertex2D {mml::vec2(1, 1) * model + pos},
                Vertex2D {mml::vec2(-1, -1) * model + pos},
                Vertex2D {mml::vec2(1, -1) * model + pos}
            };

            std::vector<GLuint> indices = {
                0, 1, 2,
                1, 2, 3
            };

            return Geometry<Vertex2D, GLuint> {vertices, indices};
        }

        Geometry<Vertex2DUV, GLuint> Shape2D::SquareUV()
        {
            std::vector<Vertex2DUV> vertices = {
                Vertex2DUV {mml::vec2(-1, 1) * model + pos, mml::vec2(0, 1)},
                Vertex2DUV {mml::vec2(1, 1) * model + pos, mml::vec2(1, 1)},
                Vertex2DUV {mml::vec2(-1, -1) * model + pos, mml::vec2(0, 0)},
                Vertex2DUV {mml::vec2(1, -1) * model + pos, mml::vec2(1, 0)}
            };

            std::vector<GLuint> indices = {
                0, 1, 2,
                1, 2, 3
            };

            return Geometry<Vertex2DUV, GLuint> {vertices, indices};
        }

        Geometry<Vertex2D, GLuint> Shape2D::Circle()
        {

            std::vector<Vertex2D> vertices(362);
            std::vector<GLuint> indices(362 * 3);

            constexpr float pi = (float)mml::PI;

            vertices[0] = Vertex2D {pos};

            for(int i = 1; i < 362; i++) {
                vertices[i] = Vertex2D {mml::vec2(cos(i * pi / 180), sin(i * pi / 180)) * model + pos};

                indices[i * 3] = i;
                indices[i * 3 + 1] = 0;
                indices[i * 3 + 2] = i + 1;
            }

            return Geometry<Vertex2D, GLuint> {vertices, indices};
        }
    }
}
