#include <graphics/geometry/shape3d.hpp>
#include <math/math.hpp>
#include <math/transform.hpp>

namespace mgl
{
    Shape3D::Shape3D(const mml::vec3& pos, const mml::vec3& scale, const mml::vec3& rotate) :
        pos(pos)
    {
        model = mml::rotate(mml::scale(mml::mat3(1), scale), rotate);
    }

    Geometry<Vertex3DUVN, GLuint> Shape3D::PlainUVN()
    {
        mml::mat3 normalModel = mml::transpose(mml::inverse(model));

        std::vector<Vertex3DUVN> vertices = {
            Vertex3DUVN {mml::vec3(-1, 0, 1) * model + pos, mml::vec2(0, 1), mml::vec3(-1, 1, 1) * normalModel},
            Vertex3DUVN {mml::vec3(1, 0, 1) * model + pos, mml::vec2(1, 1), mml::vec3(1, 1, 1) * normalModel},
            Vertex3DUVN {mml::vec3(-1, 0, -1) * model + pos, mml::vec2(0, 0), mml::vec3(-1, 1, -1) * normalModel},
            Vertex3DUVN {mml::vec3(1, 0, -1) * model + pos, mml::vec2(1, 0), mml::vec3(1, 1, -1) * normalModel}
        };

        std::vector<GLuint> indices = {
            0, 1, 2,
            1, 2, 3
        };

        return Geometry<Vertex3DUVN, GLuint> {vertices, indices};
    }

    Geometry<Vertex3D, GLuint> Shape3D::Cube()
    {
        std::vector<Vertex3D> vertices = {
            Vertex3D {mml::vec3(-1, 1, 1) * model + pos},
            Vertex3D {mml::vec3(1, 1, 1) * model + pos},
            Vertex3D {mml::vec3(-1, -1, 1) * model + pos},
            Vertex3D {mml::vec3(1, -1, 1) * model + pos},

            Vertex3D {mml::vec3(-1, 1, -1) * model + pos},
            Vertex3D {mml::vec3(1, 1, -1) * model + pos},
            Vertex3D {mml::vec3(-1, -1, -1) * model + pos},
            Vertex3D {mml::vec3(1, -1, -1) * model + pos}
        };

        std::vector<GLuint> indices = {
            0, 1, 2,
            1, 2, 3,

            4, 5, 6,
            5, 6, 7,

            0, 4, 6,
            0, 2, 6,

            1, 5, 7,
            1, 3, 7,

            0, 1, 4,
            1, 4, 5,

            2, 3, 6,
            3, 6, 7
        };

        return Geometry<Vertex3D, GLuint> {vertices, indices};
    }

    Geometry<Vertex3DN, GLuint> Shape3D::CubeN()
    {
        mml::mat3 normalModel = mml::transpose(mml::inverse(model));

        std::vector<Vertex3DN> vertices = {
            Vertex3DN {mml::vec3(-1, 1, 1) * model + pos, mml::vec3(0, 0, 1) * normalModel},
            Vertex3DN {mml::vec3(1, 1, 1) * model + pos, mml::vec3(0, 0, 1) * normalModel},
            Vertex3DN {mml::vec3(-1, -1, 1) * model + pos, mml::vec3(0, 0, 1) * normalModel},
            Vertex3DN {mml::vec3(1, -1, 1) * model + pos, mml::vec3(0, 0, 1) * normalModel},

            Vertex3DN {mml::vec3(-1, 1, -1) * model + pos, mml::vec3(0, 0, -1) * normalModel},
            Vertex3DN {mml::vec3(1, 1, -1) * model + pos, mml::vec3(0, 0, -1) * normalModel},
            Vertex3DN {mml::vec3(-1, -1, -1) * model + pos, mml::vec3(0, 0, -1) * normalModel},
            Vertex3DN {mml::vec3(1, -1, -1) * model + pos, mml::vec3(0, 0, -1) * normalModel}
        };

        std::vector<GLuint> indices = {
            0, 1, 2,
            1, 2, 3,

            4, 5, 6,
            5, 6, 7,

            8, 9, 10,
            9, 10, 11,

            12, 13, 14,
            13, 14, 15,

            16, 17, 18,
            17, 18, 19,

            20, 21, 22,
            21, 22, 23
        };

        return Geometry<Vertex3DN, GLuint> {vertices, indices};
    }

    Geometry<Vertex3DUVN, GLuint> Shape3D::CubeUVN()
    {
        mml::mat3 normalModel = mml::transpose(mml::inverse(model));

        std::vector<Vertex3DUVN> vertices = {
            Vertex3DUVN {mml::vec3(-1, 1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 0, 1) * normalModel},
            Vertex3DUVN {mml::vec3(1, 1, 1) * model + pos, mml::vec2(1, 0), mml::vec3(0, 0, 1) * normalModel},
            Vertex3DUVN {mml::vec3(-1, -1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 0, 1) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, 1) * model + pos, mml::vec2(1, 1), mml::vec3(0, 0, 1) * normalModel},

            Vertex3DUVN {mml::vec3(-1, 1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 0, -1) * normalModel},
            Vertex3DUVN {mml::vec3(1, 1, -1) * model + pos, mml::vec2(1, 1), mml::vec3(0, 0, -1) * normalModel},
            Vertex3DUVN {mml::vec3(-1, -1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 0, -1) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, -1) * model + pos, mml::vec2(1, 0), mml::vec3(0, 0, -1) * normalModel},

            Vertex3DUVN {mml::vec3(1, 1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, 1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(1, 0, 0) * normalModel},

            Vertex3DUVN {mml::vec3(-1, 1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(-1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(-1, 1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(-1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(-1, -1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(-1, 0, 0) * normalModel},
            Vertex3DUVN {mml::vec3(-1, -1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(-1, 0, 0) * normalModel},

            Vertex3DUVN {mml::vec3(-1, 1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, 1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(-1, 1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, 1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, 1, 0) * normalModel},

            Vertex3DUVN {mml::vec3(-1, -1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, -1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, 1) * model + pos, mml::vec2(0, 1), mml::vec3(0, -1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(-1, -1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, -1, 0) * normalModel},
            Vertex3DUVN {mml::vec3(1, -1, -1) * model + pos, mml::vec2(0, 1), mml::vec3(0, -1, 0) * normalModel}
        };

        std::vector<GLuint> indices = {
            0, 1, 2,
            1, 2, 3,

            4, 5, 6,
            5, 6, 7,

            8, 9, 10,
            9, 10, 11,

            12, 13, 14,
            13, 14, 15,

            16, 17, 18,
            17, 18, 19,

            20, 21, 22,
            21, 22, 23
        };

        return Geometry<Vertex3DUVN, GLuint> {vertices, indices};
    }

    Geometry<Vertex3D, GLuint> Shape3D::Sphere(uint rings, uint sectors)
    {

        std::vector<Vertex3D> vertices(rings * sectors);
        std::vector<GLuint> indices((rings - 1) * (sectors - 1) * 6);

        constexpr float pi = (float)mml::PI;
        constexpr float pi2 = pi * 2;

        float R = 1.0f / (rings - 1);
        float S = 1.0f / (sectors - 1);

        uint index = 0;

        for(uint r = 0; r < rings; r++) {
            for(uint s = 0; s < sectors; s++) {
                float y = sinf(-(pi / 2) + pi * r * R );
                float x = cosf(pi2 * s * S) * sinf(pi * r * R );
                float z = sinf(pi2 * s * S) * sinf(pi * r * R );

                vertices[index] = Vertex3D {mml::vec3(x, y, z) * model + pos};
                index++;
            }
        }

        index = 0;

        for(uint r = 0; r < rings - 1; r++) {
            for(uint s = 0; s < sectors - 1; s++) {
                indices[index] = r * sectors + s;
                index++;
                indices[index] = r * sectors + (s+1);
                index++;
                indices[index] = (r+1) * sectors + (s+1);
                index++;

                indices[index] = r * sectors + s;
                index++;
                indices[index] = (r+1) * sectors + (s+1);
                index++;
                indices[index] = (r+1) * sectors + s;
                index++;
            }
        }

        return Geometry<Vertex3D, GLuint> {vertices, indices};
    }

    Geometry<Vertex3DN, GLuint> Shape3D::SphereN(uint rings, uint sectors)
    {
        mml::mat3 normalModel = mml::transpose(mml::inverse(model));

        std::vector<Vertex3DN> vertices(rings * sectors);
        std::vector<GLuint> indices((rings - 1) * (sectors - 1) * 6);

        constexpr float pi = (float)mml::PI;
        constexpr float pi2 = pi * 2;

        float R = 1.0f / (rings - 1);
        float S = 1.0f / (sectors - 1);

        uint index = 0;

        for(uint r = 0; r < rings; r++) {
            for(uint s = 0; s < sectors; s++) {
                float y = sinf(-(pi / 2) + pi * r * R);
                float x = cosf(pi2 * s * S) * sinf(pi * r * R);
                float z = sinf(pi2 * s * S) * sinf(pi * r * R);

                vertices[index] = Vertex3DN {mml::vec3(x, y, z) * model + pos, mml::vec3(x, y, z) * normalModel};
                index++;
            }
        }

        index = 0;

        for(uint r = 0; r < rings - 1; r++) {
            for(uint s = 0; s < sectors - 1; s++) {
                indices[index] = r * sectors + s;
                index++;
                indices[index] = r * sectors + (s + 1);
                index++;
                indices[index] = (r + 1) * sectors + (s + 1);
                index++;

                indices[index] = r * sectors + s;
                index++;
                indices[index] = (r + 1) * sectors + (s + 1);
                index++;
                indices[index] = (r + 1) * sectors + s;
                index++;
            }
        }

        return Geometry<Vertex3DN, GLuint> {vertices, indices};
    }

    Geometry<Vertex3DUVN, GLuint> Shape3D::SphereUVN(uint rings, uint sectors)
    {
        mml::mat3 normalModel = mml::transpose(mml::inverse(model));

        std::vector<Vertex3DUVN> vertices(rings * sectors);
        std::vector<GLuint> indices((rings - 1) * (sectors - 1) * 6);

        constexpr float pi = (float)mml::PI;
        constexpr float pi2 = pi * 2;

        float R = 1.0f / (rings - 1);
        float S = 1.0f / (sectors - 1);

        uint index = 0;

        for(uint r = 0; r < rings; r++) {
            for(uint s = 0; s < sectors; s++) {
                float y = sinf(-(pi / 2) + pi * r * R);
                float x = cosf(pi2 * s * S) * sinf(pi * r * R);
                float z = sinf(pi2 * s * S) * sinf(pi * r * R);

                vertices[index] = Vertex3DUVN {mml::vec3(x, y, z) * model + pos, mml::vec2(x, y), mml::vec3(x, y, z) * normalModel};
                index++;
            }
        }

        index = 0;

        for(uint r = 0; r < rings - 1; r++) {
            for(uint s = 0; s < sectors - 1; s++) {
                indices[index] = r * sectors + s;
                index++;
                indices[index] = r * sectors + (s + 1);
                index++;
                indices[index] = (r + 1) * sectors + (s + 1);
                index++;

                indices[index] = r * sectors + s;
                index++;
                indices[index] = (r + 1) * sectors + (s + 1);
                index++;
                indices[index] = (r + 1) * sectors + s;
                index++;
            }
        }

        return Geometry<Vertex3DUVN, GLuint> {vertices, indices};
    }
}
