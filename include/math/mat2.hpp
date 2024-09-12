#pragma once
#include <iostream>
#include <math/mat.hpp>
#include <math/vec.hpp>
#include <math/trig.hpp>

namespace mml
{
    template<typename T>
    class Mat<T, 2, 2>
    {
    public:
        Mat() = default;
        Mat(T value);
        Mat(const T mat[4]);
        Mat(T v1, T v2, T v3, T v4);
        Mat(Mat<T, 3, 3> mat);
        Mat(Mat<T, 4, 4> mat);

        template<typename U>
        Mat(const Mat<U, 2, 2>& mat);

        Mat<T, 2, 2> rotate(T r) const;
        Mat<T, 2, 2> scale(const Vec<T, 2>& v) const;
        Mat<T, 2, 2> translate(T vec) const;

        Mat<T, 2, 2> transpose() const;
        Mat<T, 2, 2> inverse() const;

        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Mat<U, 2, 2>& mat) const;
        template<typename U>
        bool operator!=(const Mat<U, 2, 2>& mat) const;

        template<typename U>
        Mat<T, 2, 2> operator*(const Mat<U, 2, 2>& mat) const;

        template<typename U>
        Vec<T, 2> operator*(const Vec<U, 2>& vec) const;
        
    private:
        T mat[2][2] = {{0}};
    };

    template<typename T>
    Mat<T, 2, 2>::Mat(T value)
    {
        this->mat[0][0] = value;
        this->mat[0][1] = 0;
        this->mat[1][0] = 0;
        this->mat[1][1] = value;
    }

    template<typename T>
    Mat<T, 2, 2>::Mat(const T mat[4])
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }

    template<typename T>
    Mat<T, 2, 2>::Mat(T v1, T v2, T v3, T v4)
    {
        this->mat[0][0] = v1;
        this->mat[0][1] = v2;
        this->mat[1][0] = v3;
        this->mat[1][1] = v4;
    }
    
    template<typename T>
    template<typename U>
    Mat<T, 2, 2>::Mat(const Mat<U, 2, 2>& mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }

    template<typename T>
    Mat<T, 2, 2>::Mat(Mat<T, 3, 3> mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }

    template<typename T>
    Mat<T, 2, 2>::Mat(Mat<T, 4, 4> mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }


    template<typename T>
    Mat<T, 2, 2> Mat<T, 2, 2>::rotate(T r) const
    {
        Mat<T, 2, 2> rm(
            cos(r), -sin(r),
            sin(r), cos(r)
        );
        return (*this) * rm;
    }

    template<typename T>
    Mat<T, 2, 2> Mat<T, 2, 2>::scale(const Vec<T, 2>& vec) const
    {
        return Mat<T, 2, 2>(
            this->mat[0][0] * vec.x, this->mat[0][1],
            this->mat[1][0], this->mat[1][1] * vec.y
        );
    }

    template<typename T>
    Mat<T, 2, 2> Mat<T, 2, 2>::translate(T v) const
    {
        return Mat<T, 2, 2>(
            this->mat[0][0], this->mat[0][1] + v,
            this->mat[1][0], this->mat[1][1]
        );
    }

    template<typename T>
    Mat<T, 2, 2> Mat<T, 2, 2>::transpose() const
    {
        return Mat<T, 2, 2>(
            this->mat[0][0], this->mat[1][0],
            this->mat[0][1], this->mat[1][1]
        );
    }

    template<typename T>
    Mat<T, 2, 2> Mat<T, 2, 2>::inverse() const
    {
        T det = this->mat[0][0] * this->mat[1][1] -
                this->mat[0][1] * this->mat[1][0];

        T invdet = 1 / det;

        return Mat<T, 2, 2>(
            this->mat[1][1] * invdet, -this->mat[0][1] * invdet,
            -this->mat[1][0] * invdet, this->mat[0][0] * invdet
        );
    }

    template<typename T>
    T* Mat<T, 2, 2>::operator&()
    {
        return &this->mat[0][0];
    }

    template<typename T>
    T* Mat<T, 2, 2>::operator[](size_t index)
    {
        return this->mat[index];
    }

    template<typename T>
    const T* Mat<T, 2, 2>::operator[](size_t index) const
    {
        return this->mat[index];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 2, 2>::operator==(const Mat<U, 2, 2>& mat) const
    {
        return this->mat[0][0] == mat[0][0] &&
               this->mat[0][1] == mat[0][1] &&
               this->mat[1][0] == mat[1][0] &&
               this->mat[1][1] == mat[1][1];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 2, 2>::operator!=(const Mat<U, 2, 2>& mat) const
    {
        return this->mat[0][0] != mat[0][0] ||
               this->mat[0][1] != mat[0][1] ||
               this->mat[1][0] != mat[1][0] ||
               this->mat[1][1] != mat[1][1];
    }

    template<typename T>
    template<typename U>
    Mat<T, 2, 2> Mat<T, 2, 2>::operator*(const Mat<U, 2, 2>& mat) const
    {
        return Mat<T, 2, 2>(
            this->mat[0][0] * mat[0][0] + this->mat[0][1] * mat[1][0],
            this->mat[0][0] * mat[0][1] + this->mat[0][1] * mat[1][1],
            this->mat[1][0] * mat[0][0] + this->mat[1][1] * mat[1][0],
            this->mat[1][0] * mat[0][1] + this->mat[1][1] * mat[1][1]
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Mat<T, 2, 2>::operator*(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(
            this->mat[0][0] * vec.x + this->mat[0][1] * vec.y,
            this->mat[1][0] * vec.x + this->mat[1][1] * vec.y
        );
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Mat<T, 2, 2>& mat)
    {
        return out << '|' << mat[0][0] << ' ' << mat[0][1] << "|\n|"
                          << mat[1][0] << ' ' << mat[1][1] << '|';
    }
}
