#pragma once
#include <math/mat.hpp>
#include <math/vec.hpp>

namespace mml
{
    template<typename T, size_t N>
    Vec<T, N> normalize(const Vec<T, N>& vec)
    {
        return vec.normalize();
    }

    template<typename T, size_t N, size_t M>
    Mat<T, N, N> rotate(const Mat<T, N, N>& mat, const Vec<T, M>& vec)
    {
        return mat.rotate(vec);
    }

    template<typename T, size_t N>
    Mat<T, N, N> rotate(const Mat<T, N, N>& mat, T rotation)
    {
        return mat.rotate(rotation);
    }

    template<typename T, size_t N, size_t M>
    Mat<T, N, N> scale(const Mat<T, N, N>& mat, const Vec<T, M>& vec)
    {
        return mat.scale(vec);
    }
    
    template<typename T, size_t N, size_t M>
    Mat<T, N, N> translate(const Mat<T, N, N>& mat, const Vec<T, M>& vec)
    {
        return mat.translate(vec);
    }

    template<typename T, size_t N>
    Mat<T, N, N> transpose(const Mat<T, N, N>& mat)
    {
        return mat.transpose();
    }

    template<typename T, size_t N>
    Mat<T, N, N> inverse(const Mat<T, N, N>& mat)
    {
        return mat.inverse();
    }

    template<typename T, size_t N>
    Vec<T, N> rotate(const Vec<T, N>& vec, const Vec<T, N>& avec)
    {
        return vec.rotate(avec);
    }
}