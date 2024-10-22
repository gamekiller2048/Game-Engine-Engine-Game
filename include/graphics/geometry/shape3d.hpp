#pragma once
#include <vector>
#include <math/math.hpp>
#include <glad/gl.h>
#include <graphics/geometry/vertex.hpp>

namespace mgl
{
    namespace gl
    {
        class Shape3D
        {
        public:
            Shape3D(const mml::vec3& pos=mml::vec3(0), const mml::vec3& scale=mml::vec3(1), const mml::vec3& rotate=mml::vec3(0));

            mml::vec3 pos;
            mml::mat3 model;

            Geometry<Vertex3DUVN, GLuint> PlainUVN();
            Geometry<Vertex3D, GLuint> Cube();
            Geometry<Vertex3DN, GLuint> CubeN();
            Geometry<Vertex3DUVN, GLuint> CubeUVN();
            Geometry<Vertex3D, GLuint> Sphere(uint rings, uint sectors);
            Geometry<Vertex3DN, GLuint> SphereN(uint rings, uint sectors);
            Geometry<Vertex3DUVN, GLuint> SphereUVN(uint rings, uint sectors);
        };
    }
}
