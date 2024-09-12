#pragma once
#include <iostream>
#include <math/mat.hpp>
#include <math/vec.hpp>
#include <math/trig.hpp>

namespace mml
{
    template<typename T>
    class Mat<T, 4, 4>
    {
    public:
        Mat() = default;
        Mat(T value);
        Mat(const T mat[16]);
        Mat(T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3, T x4, T y4, T z4, T w4);
        Mat(Mat<T, 2, 2> mat);
        Mat(Mat<T, 3, 3> mat);

        template<typename U>
        Mat(const Mat<U, 4, 4>& mat);

        Mat<T, 4, 4> rotate(const Vec<T, 3>& vec) const;
        Mat<T, 4, 4> scale(const Vec<T, 3>& vec) const;
        Mat<T, 4, 4> translate(const Vec<T, 3>& vec) const;

        Mat<T, 4, 4> transpose() const;
        Mat<T, 4, 4> inverse() const;
            
        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Mat<U, 4, 4>& mat) const;
        template<typename U>
        bool operator!=(const Mat<U, 4, 4>& mat) const;

        template<typename U>
        Mat<T, 4, 4> operator*(const Mat<U, 4, 4>& mat) const;

        template<typename U>
        Vec<T, 4> operator*(const Vec<U, 4>& vec) const;

    private:
        T mat[4][4] = {{0}};
    };

    template<typename T>
    Mat<T, 4, 4>::Mat(T value)
    {
        this->mat[0][0] = value;
        this->mat[0][1] = 0;
        this->mat[0][2] = 0;
        this->mat[0][3] = 0;
        this->mat[1][0] = 0;
        this->mat[1][1] = value;
        this->mat[1][2] = 0;
        this->mat[1][3] = 0;
        this->mat[2][0] = 0;
        this->mat[2][1] = 0;
        this->mat[2][2] = value;
        this->mat[2][3] = 0;
        this->mat[3][0] = 0;
        this->mat[3][1] = 0;
        this->mat[3][2] = 0;
        this->mat[3][3] = value;
    }

    template<typename T>
    Mat<T, 4, 4>::Mat(const T mat[16])
    {
        memcpy(std::begin(this->mat), mat, sizeof(T) * 9);
    }

    template<typename T>
    Mat<T, 4, 4>::Mat(T x1, T y1, T z1, T w1, T x2, T y2, T z2, T w2, T x3, T y3, T z3, T w3, T x4, T y4, T z4, T w4)
    {
        this->mat[0][0] = x1;
        this->mat[0][1] = y1;
        this->mat[0][2] = z1;
        this->mat[0][3] = w1;
        this->mat[1][0] = x2;
        this->mat[1][1] = y2;
        this->mat[1][2] = z2;
        this->mat[1][3] = w2;
        this->mat[2][0] = x3;
        this->mat[2][1] = y3;
        this->mat[2][2] = z3;
        this->mat[2][3] = w3;
        this->mat[3][0] = x4;
        this->mat[3][1] = y4;
        this->mat[3][2] = z4;
        this->mat[3][3] = w4;
    }

    template<typename T>
    template<typename U>
    Mat<T, 4, 4>::Mat(const Mat<U, 4, 4>& mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[0][2] = mat[0][2];
        this->mat[0][3] = mat[0][3];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
        this->mat[1][2] = mat[1][2];
        this->mat[0][3] = mat[0][3];
        this->mat[2][0] = mat[2][0];
        this->mat[2][1] = mat[2][1];
        this->mat[2][2] = mat[2][2];
        this->mat[2][3] = mat[2][3];
        this->mat[2][0] = mat[3][0];
        this->mat[3][1] = mat[3][1];
        this->mat[3][2] = mat[3][2];
        this->mat[3][3] = mat[3][3];
    }

    template<typename T>
    Mat<T, 4, 4>::Mat(Mat<T, 2, 2> mat)
    {
        this->mat[0][0] = mat[0][0];
        this->mat[0][1] = mat[0][1];
        this->mat[1][0] = mat[1][0];
        this->mat[1][1] = mat[1][1];
    }

    template<typename T>
    Mat<T, 4, 4>::Mat(Mat<T, 3, 3> mat)
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
    Mat<T, 4, 4> Mat<T, 4, 4>::rotate(const Vec<T, 3>& vec) const
    {
        Mat<T, 4, 4> rx(
            1, 0, 0, 0,
            0, cos(vec.x), -sin(vec.x), 0,
            0, sin(vec.x), cos(vec.x), 0,
            0, 0, 0, 1
        );

        Mat<T, 4, 4> ry(
            cos(vec.y), 0, sin(vec.y), 0,
            0, 1, -sin(vec.y), 0,
            -sin(vec.y), 0, cos(vec.y), 0,
            0, 0, 0, 1
        );

        Mat<T, 4, 4> rz(
            cos(vec.z), -sin(vec.z), 0, 0,
            sin(vec.z), cos(vec.z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );

        return (*this) * rx * ry * rz;
    }

    template<typename T>
    Mat<T, 4, 4> Mat<T, 4, 4>::scale(const Vec<T, 3>& vec) const
    {
        return Mat<T, 4, 4>(
            this->mat[0][0] * vec.x, this->mat[0][1], this->mat[0][2], this->mat[0][3],
            this->mat[1][0], this->mat[1][1] * vec.y, this->mat[1][2], this->mat[1][3],
            this->mat[2][0], this->mat[2][1], this->mat[2][2] * vec.z, this->mat[2][3],
            this->mat[3][0], this->mat[3][1], this->mat[3][2], this->mat[3][3]
        );
    }

    template<typename T>
    Mat<T, 4, 4> Mat<T, 4, 4>::translate(const Vec<T, 3>& vec) const
    {
        return Mat<T, 4, 4>(
            this->mat[0][0], this->mat[0][1], this->mat[0][2], this->mat[0][3] + vec.x,
            this->mat[1][0], this->mat[1][1], this->mat[1][2], this->mat[1][3] + vec.y,
            this->mat[2][0], this->mat[2][1], this->mat[2][2], this->mat[2][3] + vec.z,
            this->mat[3][0], this->mat[3][1], this->mat[3][2], this->mat[3][3]
        );
    }

    template<typename T>
    Mat<T, 4, 4> Mat<T, 4, 4>::transpose() const
    {
        return Mat<T, 4, 4>(
            this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0],
            this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1],
            this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2],
            this->mat[0][3], this->mat[1][3], this->mat[2][3], this->mat[3][3]
        );
    }

    template<typename T>
    Mat<T, 4, 4> Mat<T, 4, 4>::inverse() const
    {
        T det = this->mat[0][0] * (this->mat[1][1] * (this->mat[2][2] * this->mat[3][3] - this->mat[2][3] * this->mat[3][2]) -
                this->mat[1][2] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1]) +
                this->mat[1][3] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1])) -
                this->mat[0][1] * (this->mat[1][0] * (this->mat[2][2] * this->mat[3][3] - this->mat[2][3] * this->mat[3][2]) -
                this->mat[1][2] * (this->mat[2][0] * this->mat[3][3] - this->mat[2][3] * this->mat[3][0]) +
                this->mat[1][3] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0])) +
                this->mat[0][2] * (this->mat[1][0] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1]) -
                this->mat[1][1] * (this->mat[2][0] * this->mat[3][3] - this->mat[2][3] * this->mat[3][0]) +
                this->mat[1][3] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0])) -
                this->mat[0][3] * (this->mat[1][0] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1]) -
                this->mat[1][1] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0]) +
                this->mat[1][2] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0]));


        T invdet = 1 / det;

        return Mat<T, 4, 4>(
            ((this->mat[1][1] * (this->mat[2][2] * this->mat[3][3] - this->mat[2][3] * this->mat[3][2]) - this->mat[1][2] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1]) + this->mat[1][3] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1])) * invdet),
            ((this->mat[0][2] * (this->mat[2][3] * this->mat[3][1] - this->mat[2][1] * this->mat[3][3]) - this->mat[0][1] * (this->mat[2][3] * this->mat[3][2] - this->mat[2][2] * this->mat[3][3]) + this->mat[0][3] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1])) * invdet),
            ((this->mat[0][1] * (this->mat[1][3] * this->mat[3][2] - this->mat[1][2] * this->mat[3][3]) - this->mat[0][2] * (this->mat[1][3] * this->mat[3][1] - this->mat[1][1] * this->mat[3][3]) + this->mat[0][3] * (this->mat[1][2] * this->mat[3][1] - this->mat[1][1] * this->mat[3][2])) * invdet),
            ((this->mat[0][2] * (this->mat[1][1] * this->mat[2][3] - this->mat[1][3] * this->mat[2][1]) - this->mat[0][1] * (this->mat[1][0] * this->mat[2][3] - this->mat[1][3] * this->mat[2][0]) + this->mat[0][3] * (this->mat[1][0] * this->mat[2][1] - this->mat[1][1] * this->mat[2][0])) * invdet),

            ((this->mat[1][2] * (this->mat[2][3] * this->mat[3][0] - this->mat[2][0] * this->mat[3][3]) - this->mat[1][0] * (this->mat[2][3] * this->mat[3][2] - this->mat[2][2] * this->mat[3][3]) + this->mat[1][3] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0])) * invdet),
            ((this->mat[0][0] * (this->mat[2][3] * this->mat[3][2] - this->mat[2][2] * this->mat[3][3]) - this->mat[0][2] * (this->mat[2][3] * this->mat[3][0] - this->mat[2][0] * this->mat[3][3]) + this->mat[0][3] * (this->mat[2][2] * this->mat[3][0] - this->mat[2][0] * this->mat[3][2])) * invdet),
            ((this->mat[0][2] * (this->mat[1][0] * this->mat[3][3] - this->mat[1][3] * this->mat[3][0]) - this->mat[0][0] * (this->mat[1][2] * this->mat[3][3] - this->mat[1][3] * this->mat[3][2]) + this->mat[0][3] * (this->mat[1][2] * this->mat[3][0] - this->mat[1][0] * this->mat[3][2])) * invdet),
            ((this->mat[0][0] * (this->mat[1][2] * this->mat[2][3] - this->mat[1][3] * this->mat[2][2]) - this->mat[0][2] * (this->mat[1][0] * this->mat[2][3] - this->mat[1][3] * this->mat[2][0]) + this->mat[0][3] * (this->mat[1][0] * this->mat[2][2] - this->mat[1][2] * this->mat[2][0])) * invdet),

            ((this->mat[1][0] * (this->mat[2][1] * this->mat[3][3] - this->mat[2][3] * this->mat[3][1]) - this->mat[1][1] * (this->mat[2][0] * this->mat[3][3] - this->mat[2][3] * this->mat[3][0]) + this->mat[1][3] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][1] * (this->mat[2][3] * this->mat[3][0] - this->mat[2][0] * this->mat[3][3]) - this->mat[0][0] * (this->mat[2][3] * this->mat[3][1] - this->mat[2][1] * this->mat[3][3]) + this->mat[0][3] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][0] * (this->mat[1][1] * this->mat[3][3] - this->mat[1][3] * this->mat[3][1]) - this->mat[0][1] * (this->mat[1][0] * this->mat[3][3] - this->mat[1][3] * this->mat[3][0]) + this->mat[0][3] * (this->mat[1][0] * this->mat[3][1] - this->mat[1][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][1] * (this->mat[1][3] * this->mat[2][0] - this->mat[1][0] * this->mat[2][3]) - this->mat[0][0] * (this->mat[1][2] * this->mat[2][3] - this->mat[1][3] * this->mat[2][2]) + this->mat[0][3] * (this->mat[1][0] * this->mat[2][2] - this->mat[1][2] * this->mat[2][0])) * invdet),

            ((this->mat[1][1] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0]) - this->mat[1][0] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1]) + this->mat[1][2] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][0] * (this->mat[2][1] * this->mat[3][2] - this->mat[2][2] * this->mat[3][1]) - this->mat[0][1] * (this->mat[2][0] * this->mat[3][2] - this->mat[2][2] * this->mat[3][0]) + this->mat[0][2] * (this->mat[2][0] * this->mat[3][1] - this->mat[2][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][1] * (this->mat[1][2] * this->mat[3][0] - this->mat[1][0] * this->mat[3][2]) - this->mat[0][0] * (this->mat[1][1] * this->mat[3][2] - this->mat[1][2] * this->mat[3][1]) + this->mat[0][2] * (this->mat[1][0] * this->mat[3][1] - this->mat[1][1] * this->mat[3][0])) * invdet),
            ((this->mat[0][0] * (this->mat[1][1] * this->mat[2][2] - this->mat[1][2] * this->mat[2][1]) - this->mat[0][1] * (this->mat[1][0] * this->mat[2][2] - this->mat[1][2] * this->mat[2][0]) + this->mat[0][2] * (this->mat[1][0] * this->mat[2][1] - this->mat[1][1] * this->mat[2][0])) * invdet)
        );
    }

    template<typename T>
    T* Mat<T, 4, 4>::operator&()
    {
        return &this->mat[0][0];
    }

    template<typename T>
    T* Mat<T, 4, 4>::operator[](size_t index)
    {
        return this->mat[index];
    }

    template<typename T>
    const T* Mat<T, 4, 4>::operator[](size_t index) const
    {
        return this->mat[index];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 4, 4>::operator==(const Mat<U, 4, 4>& mat) const
    {
        return this->mat[0][0] == mat[0][0] &&
               this->mat[0][1] == mat[0][1] &&
               this->mat[0][2] == mat[0][2] &&
               this->mat[0][3] == mat[0][3] &&
               this->mat[1][0] == mat[1][0] &&
               this->mat[1][1] == mat[1][1] &&
               this->mat[1][2] == mat[1][2] &&
               this->mat[1][3] == mat[1][3] &&
               this->mat[2][0] == mat[2][0] &&
               this->mat[2][1] == mat[2][1] &&
               this->mat[2][2] == mat[2][2] &&
               this->mat[2][3] == mat[2][3] &&
               this->mat[3][0] == mat[3][0] &&
               this->mat[3][1] == mat[3][1] &&
               this->mat[3][2] == mat[3][2] &&
               this->mat[3][3] == mat[3][3];
    }

    template<typename T>
    template<typename U>
    bool Mat<T, 4, 4>::operator!=(const Mat<U, 4, 4>& mat) const
    {
        return this->mat[0][0] != mat[0][0] ||
               this->mat[0][1] != mat[0][1] ||
               this->mat[0][2] != mat[0][2] ||
               this->mat[0][3] != mat[0][3] ||
               this->mat[1][0] != mat[1][0] ||
               this->mat[1][1] != mat[1][1] ||
               this->mat[1][2] != mat[1][2] ||
               this->mat[1][3] != mat[1][3] ||
               this->mat[2][0] != mat[2][0] ||
               this->mat[2][1] != mat[2][1] ||
               this->mat[2][2] != mat[2][2] ||
               this->mat[2][3] != mat[2][3] ||
               this->mat[3][0] != mat[3][0] ||
               this->mat[3][1] != mat[3][1] ||
               this->mat[3][2] != mat[3][2] ||
               this->mat[3][3] != mat[3][3];
    }

    template<typename T>
    template<typename U>
    Mat<T, 4, 4> Mat<T, 4, 4>::operator*(const Mat<U, 4, 4>& mat) const
    {
        return Mat<T, 4, 4>(
            this->mat[0][0] * mat[0][0] + this->mat[0][1] * mat[1][0] + this->mat[0][2] * mat[2][0] + this->mat[0][3] * mat[3][0],
            this->mat[0][0] * mat[0][1] + this->mat[0][1] * mat[1][1] + this->mat[0][2] * mat[2][1] + this->mat[0][3] * mat[3][1],
            this->mat[0][0] * mat[0][2] + this->mat[0][1] * mat[1][2] + this->mat[0][2] * mat[2][2] + this->mat[0][3] * mat[3][2],
            this->mat[0][0] * mat[0][3] + this->mat[0][1] * mat[1][3] + this->mat[0][2] * mat[2][3] + this->mat[0][3] * mat[3][3],

            this->mat[1][0] * mat[0][0] + this->mat[1][1] * mat[1][0] + this->mat[1][2] * mat[2][0] + this->mat[1][3] * mat[3][0],
            this->mat[1][0] * mat[0][1] + this->mat[1][1] * mat[1][1] + this->mat[1][2] * mat[2][1] + this->mat[1][3] * mat[3][1],
            this->mat[1][0] * mat[0][2] + this->mat[1][1] * mat[1][2] + this->mat[1][2] * mat[2][2] + this->mat[1][3] * mat[3][2],
            this->mat[1][0] * mat[0][3] + this->mat[1][1] * mat[1][3] + this->mat[1][2] * mat[2][3] + this->mat[1][3] * mat[3][3],

            this->mat[2][0] * mat[0][0] + this->mat[2][1] * mat[1][0] + this->mat[2][2] * mat[2][0] + this->mat[2][3] * mat[3][0],
            this->mat[2][0] * mat[0][1] + this->mat[2][1] * mat[1][1] + this->mat[2][2] * mat[2][1] + this->mat[2][3] * mat[3][1],
            this->mat[2][0] * mat[0][2] + this->mat[2][1] * mat[1][2] + this->mat[2][2] * mat[2][2] + this->mat[2][3] * mat[3][2],
            this->mat[2][0] * mat[0][3] + this->mat[2][1] * mat[1][3] + this->mat[2][2] * mat[2][3] + this->mat[2][3] * mat[3][3],

            this->mat[3][0] * mat[0][0] + this->mat[3][1] * mat[1][0] + this->mat[3][2] * mat[2][0] + this->mat[3][3] * mat[3][0],
            this->mat[3][0] * mat[0][1] + this->mat[3][1] * mat[1][1] + this->mat[3][2] * mat[2][1] + this->mat[3][3] * mat[3][1],
            this->mat[3][0] * mat[0][2] + this->mat[3][1] * mat[1][2] + this->mat[3][2] * mat[2][2] + this->mat[3][3] * mat[3][2],
            this->mat[3][0] * mat[0][3] + this->mat[3][1] * mat[1][3] + this->mat[3][2] * mat[2][3] + this->mat[3][3] * mat[3][3]
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Mat<T, 4, 4>::operator*(const Vec<U, 4>& vec) const
    {
        return Vec<T, 4>(
            this->mat[0][0] * vec.x + this->mat[0][1] * vec.y + this->mat[0][2] * vec.z + this->mat[0][3] * vec.w,
            this->mat[1][0] * vec.x + this->mat[1][1] * vec.y + this->mat[1][2] * vec.z + this->mat[1][3] * vec.w,
            this->mat[2][0] * vec.x + this->mat[2][1] * vec.y + this->mat[2][2] * vec.z + this->mat[2][3] * vec.w,
            this->mat[3][0] * vec.x + this->mat[3][1] * vec.y + this->mat[3][2] * vec.z + this->mat[3][3] * vec.w
        );
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Mat<T, 4, 4>& mat)
    {
        return out << '|' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << ' ' << mat[0][3] << "|\n|"
                          << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << ' ' << mat[1][3] << "|\n|"
                          << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << ' ' << mat[2][3] << "|\n|"
                          << mat[3][0] << ' ' << mat[3][1] << ' ' << mat[3][2] << ' ' << mat[3][3] << '|';
    }
}
