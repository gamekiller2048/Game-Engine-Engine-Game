#pragma once
#include <iostream>
#include <math/mat.hpp>
#include <math/vec.hpp>
#include <math/trig.hpp>

namespace mml
{
    template<typename T>
    class Vec3;


    template<typename T>
    class Mat<T, 3, 3>
    {
    public:
        Mat() = default;
        Mat(T value);
        Mat(const T mat[9]);
        Mat(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9);
        Mat(Mat<T, 2, 2> mat);
        Mat(Mat<T, 4, 4> mat);

        template<typename U>
        Mat(const Mat<U, 3, 3>& mat);

        Mat<T, 3, 3> rotate(const Vec<T, 3>& vec) const;
        Mat<T, 3, 3> scale(const Vec<T, 3>& vec) const;
        Mat<T, 3, 3> translate(const Vec<T, 2>& vec) const;

        Mat<T, 3, 3> transpose() const;
        Mat<T, 3, 3> inverse() const;

        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Mat<U, 3, 3>& mat) const;
        template<typename U>
        bool operator!=(const Mat<U, 3, 3>& mat) const;

        template<typename U>
        Mat<T, 3, 3> operator*(const Mat<U, 3, 3>& mat) const;

        template<typename U>
        Vec<T, 3> operator*(const Vec<U, 3>& vec) const;

    private:
        T mat[3][3] = {{0}};
    };

    template<typename T>
    Mat<T, 3, 3>::Mat(T value)
    {
        this->mat[0][0] = value;
        this->mat[0][1] = 0;
        this->mat[0][2] = 0;
        this->mat[1][0] = 0;
        this->mat[1][1] = value;
        this->mat[1][2] = 0;
        this->mat[2][0] = 0;
        this->mat[2][1] = 0;
        this->mat[2][2] = value;
    }

    template<typename T>
    Mat<T, 3, 3>::Mat(const T mat[9])
    {
        memcpy(std::begin(this->mat), mat, sizeof(T) * 9);
    }

    template<typename T>
    Mat<T, 3, 3>::Mat(T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9)
    {
        this->mat[0][0] = v1;
        this->mat[0][1] = v2;
        this->mat[0][2] = v3;
        this->mat[1][0] = v4;
        this->mat[1][1] = v5;
        this->mat[1][2] = v6;
        this->mat[2][0] = v7;
        this->mat[2][1] = v8;
        this->mat[2][2] = v9;
    }

    template<typename T>
    template<typename U>
    Mat<T, 3, 3>::Mat(const Mat<U, 3, 3>& mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[0][2] = mat[0][2];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
        this->mat[1][2] = mat[1][2];
        this->mat[2][0] = mat[2][0];
        this->mat[2][1] = mat[2][1];
        this->mat[2][2] = mat[2][2];
    }
    
    template<typename T>
    Mat<T, 3, 3>::Mat(Mat<T, 2, 2> mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }

    template<typename T>
    Mat<T, 3, 3>::Mat(Mat<T, 4, 4> mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[0][2] = mat[0][2];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
        this->mat[1][2] = mat[1][2];
        this->mat[2][0] = mat[2][0];
        this->mat[2][1] = mat[2][1];
        this->mat[2][2] = mat[2][2];
    }


    template<typename T>
    Mat<T, 3, 3> Mat<T, 3, 3>::rotate(const Vec<T, 3>& vec) const
    {
        Mat<T, 3, 3> rx(
            1, 0, 0,
            0, cos(vec.x), -sin(vec.x),
            0, sin(vec.x), cos(vec.x)
        );

        Mat<T, 3, 3> ry(
            cos(vec.y), 0, sin(vec.y),
            0, 1, -sin(vec.y),
            -sin(vec.y), 0, cos(vec.y)
        );

        Mat<T, 3, 3> rz(
            cos(vec.z), -sin(vec.z), 0,
            sin(vec.z), cos(vec.z), 0,
            0, 0, 1
        );

        return (*this) * rx * ry * rz;
    }

    template<typename T>
    Mat<T, 3, 3> Mat<T, 3, 3>::scale(const Vec<T, 3>& vec) const
    {
        return Mat<T, 3, 3>(
            this->mat[0][0] * vec.x, this->mat[0][1], this->mat[0][2],
            this->mat[1][0], this->mat[1][1] * vec.y, this->mat[1][2],
            this->mat[2][0], this->mat[2][1], this->mat[2][2] * vec.z
        );
    }

    template<typename T>
    Mat<T, 3, 3> Mat<T, 3, 3>::translate(const Vec<T, 2>& vec) const
    {
        return Mat<T, 3, 3>(
            this->mat[0][0], this->mat[0][1], this->mat[0][2] + vec.x,
            this->mat[1][0], this->mat[1][1], this->mat[1][2] + vec.y,
            this->mat[2][0], this->mat[2][1], this->mat[2][2]
        );
    }

    template<typename T>
    Mat<T, 3, 3> Mat<T, 3, 3>::transpose() const
    {
        return Mat<T, 3, 3>(
            this->mat[0][0], this->mat[1][0], this->mat[2][0],
            this->mat[0][1], this->mat[1][1], this->mat[2][1],
            this->mat[0][2], this->mat[1][2], this->mat[2][2]
        );
    }

    template<typename T>
    Mat<T, 3, 3> Mat<T, 3, 3>::inverse() const
    {
        T det = this->mat[0][0] * (this->mat[1][1] * this->mat[2][2] - this->mat[2][1] * this->mat[1][2]) -
                this->mat[0][1] * (this->mat[1][0] * this->mat[2][2] - this->mat[1][2] * this->mat[2][0]) +
                this->mat[0][2] * (this->mat[1][0] * this->mat[2][1] - this->mat[1][1] * this->mat[2][0]);

        T invdet = 1 / det;

        return Mat<T, 3, 3>(
            (this->mat[1][1] * this->mat[2][2] - this->mat[2][1] * this->mat[1][2]) * invdet, (this->mat[0][2] * this->mat[2][1] - this->mat[0][1] * this->mat[2][2]) * invdet, (this->mat[0][1] * this->mat[1][2] - this->mat[0][2] * this->mat[1][1]) * invdet,
            (this->mat[1][2] * this->mat[2][0] - this->mat[1][0] * this->mat[2][2]) * invdet, (this->mat[0][0] * this->mat[2][2] - this->mat[0][2] * this->mat[2][0]) * invdet, (this->mat[1][0] * this->mat[0][2] - this->mat[0][0] * this->mat[1][2]) * invdet,
            (this->mat[1][0] * this->mat[2][1] - this->mat[2][0] * this->mat[1][1]) * invdet, (this->mat[2][0] * this->mat[0][1] - this->mat[0][0] * this->mat[2][1]) * invdet, (this->mat[0][0] * this->mat[1][1] - this->mat[1][0] * this->mat[0][1]) * invdet
        );
    }

    template<typename T>
    T* Mat<T, 3, 3>::operator&()
    {
        return &this->mat[0][0];
    }

    template<typename T>
    T* Mat<T, 3, 3>::operator[](size_t index)
    {
        return this->mat[index];
    }

    template<typename T>
    const T* Mat<T, 3, 3>::operator[](size_t index) const
    {
        return this->mat[index];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 3, 3>::operator==(const Mat<U, 3, 3>& mat) const
    {
        return this->mat[0][0] == mat[0][0] &&
               this->mat[0][1] == mat[0][1] &&
               this->mat[0][2] == mat[0][2] &&
               this->mat[1][0] == mat[1][0] &&
               this->mat[1][1] == mat[1][1] &&
               this->mat[1][2] == mat[1][2] &&
               this->mat[2][0] == mat[2][0] &&
               this->mat[2][1] == mat[2][1] &&
               this->mat[2][2] == mat[2][2];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 3, 3>::operator!=(const Mat<U, 3, 3>& mat) const
    {
        return this->mat[0][0] != mat[0][0] ||
               this->mat[0][1] != mat[0][1] ||
               this->mat[0][2] != mat[0][2] ||
               this->mat[1][0] != mat[1][0] ||
               this->mat[1][1] != mat[1][1] ||
               this->mat[1][2] != mat[1][2] ||
               this->mat[2][0] != mat[2][0] ||
               this->mat[2][1] != mat[2][1] ||
               this->mat[2][2] != mat[2][2];
    }

    template<typename T>
    template<typename U>
    Mat<T, 3, 3> Mat<T, 3, 3>::operator*(const Mat<U, 3, 3>& mat) const
    {
        return Mat<T, 3, 3>(
            this->mat[0][0] * mat[0][0] + this->mat[0][1] * mat[1][0] + this->mat[0][2] * mat[2][0],
            this->mat[0][0] * mat[0][1] + this->mat[0][1] * mat[1][1] + this->mat[0][2] * mat[2][1],
            this->mat[0][0] * mat[0][2] + this->mat[0][1] * mat[1][2] + this->mat[0][2] * mat[2][2],

            this->mat[1][0] * mat[0][0] + this->mat[1][1] * mat[1][0] + this->mat[1][2] * mat[2][0],
            this->mat[1][0] * mat[0][1] + this->mat[1][1] * mat[1][1] + this->mat[1][2] * mat[2][1],
            this->mat[1][0] * mat[0][2] + this->mat[1][1] * mat[1][2] + this->mat[1][2] * mat[2][2],

            this->mat[2][0] * mat[0][0] + this->mat[2][1] * mat[1][0] + this->mat[2][2] * mat[2][0],
            this->mat[2][0] * mat[0][1] + this->mat[2][1] * mat[1][1] + this->mat[2][2] * mat[2][1],
            this->mat[2][0] * mat[0][2] + this->mat[2][1] * mat[1][2] + this->mat[2][2] * mat[2][2]
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Mat<T, 3, 3>::operator*(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(
            this->mat[0][0] * vec.x + this->mat[0][1] * vec.y + this->mat[0][2] * vec.z,
            this->mat[1][0] * vec.x + this->mat[1][1] * vec.y + this->mat[1][2] * vec.z,
            this->mat[2][0] * vec.x + this->mat[2][1] * vec.y + this->mat[2][2] * vec.z
        );
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Mat<T, 3, 3>& mat)
    {
        return out << '|' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << "|\n|"
                          << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << "|\n|"
                          << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << '|';
    }
}
