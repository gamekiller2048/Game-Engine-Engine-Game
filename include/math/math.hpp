#pragma once
#include <math/common.hpp>
#include <math/trig.hpp>
#include <math/vec2.hpp>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/mat2.hpp>
#include <math/mat3.hpp>
#include <math/mat4.hpp>
#include <math/color.hpp>
#include <math/RGBcolor.hpp>
#include <cstdint>

namespace mml
{   
    typedef Vec<float, 2> vec2;
    typedef Vec<int, 2> ivec2;
    typedef Vec<double, 2> dvec2;
    typedef Vec<long double, 2> lvec2;
    typedef Vec<uint, 2> uvec2;

    typedef Vec<float, 3> vec3;
    typedef Vec<int, 3> ivec3;
    typedef Vec<double, 3> dvec3;
    typedef Vec<uint, 3> uvec3;

    inline vec3 RIGHT = vec3(1, 0, 0);
    inline vec3 LEFT = vec3(-1, 0, 0);
    inline vec3 UP = vec3(0, 1, 0);
    inline vec3 DOWN = vec3(0, -1, 0);
    inline vec3 FORWARD = vec3(0, 0, 1);
    inline vec3 BACKWARD = vec3(0, 0, -1);

    typedef Vec<float, 4> vec4;
    typedef Vec<int, 4> ivec4;
    typedef Vec<double, 4> dvec4;
    typedef Vec<long double, 3> lvec3;
    typedef Vec<uint, 4> uvec4;

    typedef Mat<float, 2, 2> mat2;
    typedef Mat<int, 2, 2> imat2;
    typedef Mat<double, 2, 2> dmat2;
    typedef Mat<long double, 2, 2> lmat2;
    typedef Mat<uint, 2, 2> umat2;

    typedef Mat<float, 3, 3> mat3;
    typedef Mat<int, 3, 3> imat3;
    typedef Mat<double, 3, 3> dmat3;
    typedef Mat<long double, 3, 3> lmat3;
    typedef Mat<uint, 3, 3> umat3;

    typedef Mat<float, 4, 4> mat4;
    typedef Mat<int, 4, 4> imat4;
    typedef Mat<double, 4, 4> dmat4;
    typedef Mat<long double, 4, 4> lmat4;
    typedef Mat<uint, 4, 4> umat4;

    typedef Col<float, 4> color;
    typedef Col<int, 4> icolor;
    typedef Col<double, 4> dcolor;
    typedef Col<long double, 4> lcolor;
    typedef Col<uint, 4> ucolor;
    typedef Col<ubyte, 4> color8;

    typedef Col<float, 3> RGBColor;
    typedef Col<int, 3> iRGBColor;
    typedef Col<double, 3> dRGBColor;
    typedef Col<long double, 3> lRGBcolor;
    typedef Col<uint, 3> uRGBColor;
    typedef Col<ubyte, 3> RGBColor8;
}
