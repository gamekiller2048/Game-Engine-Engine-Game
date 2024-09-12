#pragma once
#include <iostream>
#include <math/vec.hpp>
#include <math/col.hpp>
#include <math/mat.hpp>
#include <math/common.hpp>

namespace mml
{
    template<typename T>
    class Vec<T, 4>
    {
    public:
        union {
            struct {
                T x;
                T y;
                T z;
                T w;
            };
            T data[4];
        };

        Vec() = default;
        Vec(T value);
        Vec(T x, T y, T z, T w);
        static Vec<T, 4> fromArray(const T data[4]);

        template<typename U>
        Vec(const Vec<U, 4>& vec);

        template<typename U>
        explicit Vec(const Col<U, 4>& col);

        float length() const;
        Vec<T, 4> floor() const;
        Vec<T, 4> ceil() const;
        Vec<T, 4> mod(const Vec<T, 4>& vec) const;
        Vec<T, 4> normalize() const;

        template<typename U>
        float dot(const Vec<U, 4>& vec) const;

        Vec<T, 4> rotate(const Vec<T, 3>& vec) const;

        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Vec<U, 4>& vec) const;
        template<typename U>
        bool operator!=(const Vec<U, 4>& vec) const;

        template<typename U>
        Vec<T, 4> operator+(const Vec<U, 4>& vec) const;
        template<typename U>
        Vec<T, 4> operator+(U value) const;
        template<typename U>
        Vec<T, 4>& operator+=(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4>& operator+=(U value);

        template<typename U>
        Vec<T, 4> operator-(const Vec<U, 4>& vec) const;
        template<typename U>
        Vec<T, 4> operator-(U value) const;
        Vec<T, 4> operator-() const;
        template<typename U>
        Vec<T, 4>& operator-=(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4>& operator-=(U value);

        template<typename U>
        Vec<T, 4> operator*(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4> operator*(U value) const;
        template<typename U>
        Vec<T, 4> operator*(const Mat<U, 4, 4>& mat) const;
        template<typename U>
        Vec<T, 4>& operator*=(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4>& operator*=(U value);

        template<typename U>
        Vec<T, 4> operator/(const Vec<U, 4>& vec) const;
        template<typename U>
        Vec<T, 4> operator/(U value) const;
        template<typename U>
        Vec<T, 4>& operator/=(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4>& operator/=(U value);

        template<typename U>
        Vec<T, 4> operator%(const Vec<U, 4>& vec) const;
        template<typename U>
        Vec<T, 4> operator%(U value) const;
        template<typename U>
        Vec<T, 4>& operator%=(const Vec<U, 4>& vec);
        template<typename U>
        Vec<T, 4>& operator%=(U value);
    };

    template<typename T>
    Vec<T, 4>::Vec(T value) :
        x(value), y(value), z(value), w(value) {}

    template<typename T>
    Vec<T, 4>::Vec(T x, T y, T z, T w) :
        x(x), y(y), z(z), w(w) {}

    template<typename T>
    Vec<T, 4> Vec<T, 4>::fromArray(const T data[4])
    {
        return Vec<T, 4>(data[0], data[1], data[2], data[3]);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>::Vec(const Vec<U, 4>& vec) :
        x((T)vec.x), y((T)vec.y), z((T)vec.z), w((T)vec.w) {}

    template<typename T>
    template<typename U>
    Vec<T, 4>::Vec(const Col<U, 4>& col) :
        x((T)col.r), y((T)col.g), z((T)col.b), w((T)col.a) {}


    template<typename T>
    float Vec<T, 4>::length() const
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::floor() const
    {
        return Vec<T, 4>(mml::floor(this->x), mml::floor(this->y), mml::floor(this->z), mml::floor(this->w));
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::ceil() const
    {
        return Vec<T, 4>(mml::ceil(this->x), mml::ceil(this->y), mml::ceil(this->z), mml::ceil(this->w));
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::mod(const Vec<T, 4>& vec) const
    {
        return Vec<T, 4>(mml::mod(this->x, vec.x), mml::mod(this->y, vec.y), mml::mod(this->z, vec.z), mml::mod(this->w, vec.w));
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::normalize() const
    {
        return Vec<T, 4>(this->x, this->y, this->z, this->w) / this->length();
    }

    template<typename T>
    template<typename U>
    float Vec<T, 4>::dot(const Vec<U, 4>& vec) const
    {
        return this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w;
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::rotate(const Vec<T, 3>& vec) const
    {
        Mat<T, 4, 4> rx(
            1, 0, 0, 0,
            0, cos(vec.x), -sin(vec.x), 0,
            0, sin(vec.x), cos(vec.x), 0,
            0, 0, 0, 1
        );

        Mat<T, 4, 4> ry(
            cos(vec.y), 0, sin(vec.y), 0,
            0, 1, 0, 0,
            -sin(vec.y), 0, cos(vec.y), 0,
            0, 0, 0, 1
        );

        Mat<T, 4, 4> rz(
            cos(vec.z), -sin(vec.z), 0, 0,
            sin(vec.z), cos(vec.z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );

        return Vec<T, 4>(this->x, this->y, this->z, this->w) * rx * ry * rz;
    }


    template<typename T>
    T* Vec<T, 4>::operator&()
    {
        return &this->data[0];
    }

    template<typename T>
    T* Vec<T, 4>::operator[](size_t index)
    {
        return this->data[index];
    }

    template<typename T>
    const T* Vec<T, 4>::operator[](size_t index) const
    {
        return this->data[index];
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 4>::operator==(const Vec<U, 4>& vec) const
    {
        return this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w;
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 4>::operator!=(const Vec<U, 4>& vec) const
    {
        return this->x != vec.x || this->y != vec.y || this->z != vec.z || this->w != vec.w;
    }


    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator+(const Vec<U, 4>& vec) const
    {
        return Vec<T, 4>(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator+(U value) const
    {
        return Vec<T, 4>(this->x + value, this->y + value, this->z + value, this->w + value);
    }

    template<typename T, typename U>
    Vec<T, 4> operator+(U value, Vec<T, 4> vec)
    {
        return Vec<T, 4>(vec.x + value, vec.y + value, vec.z + value, vec.w + value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator+=(const Vec<U, 4>& vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;
        this->w += vec.w;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator+=(U value)
    {
        this->x += value;
        this->y += value;
        this->z += value;
        this->w += value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator-(const Vec<U, 4>& vec) const
    {
        return Vec<T, 4>(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator-(U value) const
    {
        return Vec<T, 4>(this->x - value, this->y - value, this->z - value, this->w - value);
    }

    template<typename T, typename U>
    Vec<T, 4> operator-(U value, Vec<T, 4> vec)
    {
        return Vec<T, 4>(vec.x - value, vec.y - value, vec.z - value, vec.w - value);
    }

    template<typename T>
    Vec<T, 4> Vec<T, 4>::operator-() const
    {
        return Vec<T, 4>(-this->x, -this->y, -this->z, -this->w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator-=(const Vec<U, 4>& vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;
        this->z -= vec.z;
        this->w -= vec.w;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator-=(U value)
    {
        this->x -= value;
        this->y -= value;
        this->z -= value;
        this->w -= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator*(const Vec<U, 4>& vec)
    {
        return Vec<T, 4>(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator*(U value) const
    {
        return Vec<T, 4>(this->x * value, this->y * value, this->z * value, this->w * value);
    }

    template<typename T, typename U>
    Vec<T, 4> operator*(U value, Vec<T, 4> vec)
    {
        return Vec<T, 4>(vec.x * value, vec.y * value, vec.z * value, vec.w * value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator*(const Mat<U, 4, 4>& mat) const
    {
        return Vec<T, 4>(
            mat[0][0] * this->x + mat[1][0] * this->y + mat[2][0] * this->z + mat[3][0] * this->w,
            mat[0][1] * this->x + mat[1][1] * this->y + mat[2][1] * this->z + mat[3][1] * this->w,
            mat[0][2] * this->x + mat[1][2] * this->y + mat[2][2] * this->z + mat[3][2] * this->w,
            mat[0][3] * this->x + mat[1][3] * this->y + mat[2][3] * this->z + mat[3][3] * this->w
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator*=(const Vec<U, 4>& vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;
        this->z *= vec.z;
        this->w *= vec.w;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator*=(U value)
    {
        this->x *= value;
        this->y *= value;
        this->z *= value;
        this->w *= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator/(const Vec<U, 4>& vec) const
    {
        return Vec<T, 4>(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator/(U value) const
    {
        return Vec<T, 4>(this->x / value, this->y / value, this->z / value, this->w / value);
    }

    template<typename T, typename U>
    Vec<T, 4> operator/(U value, Vec<T, 4> vec)
    {
        return Vec<T, 4>(vec.x / value, vec.y / value, vec.z / value, vec.w / value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator/=(const Vec<U, 4>& vec)
    {
        this->x /= vec.x;
        this->y /= vec.y;
        this->z /= vec.z;
        this->w /= vec.w;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator/=(U value)
    {
        this->x /= value;
        this->y /= value;
        this->z /= value;
        this->w /= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator%(const Vec<U, 4>& vec) const
    {
        return Vec<T, 4>(this->x % vec.x, this->y % vec.y, this->z % vec.z, this->w % vec.w);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4> Vec<T, 4>::operator%(U value) const
    {
        return Vec<T, 4>(this->x % value, this->y % value, this->z % value, this->w % value);
    }

    template<typename T, typename U>
    Vec<T, 4> operator%(U value, Vec<T, 4> vec)
    {
        return Vec<T, 4>(vec.x % value, vec.y % value, vec.z % value, vec.w % value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator%=(const Vec<U, 4>& vec)
    {
        this->x %= vec.x;
        this->y %= vec.y;
        this->z %= vec.z;
        this->w %= vec.w;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 4>& Vec<T, 4>::operator%=(U value)
    {
        this->x %= value;
        this->y %= value;
        this->z %= value;
        this->w %= value;

        return *this;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vec<T, 4>& vec)
    {
        return out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';
    }
}

namespace std
{
    template<typename T>
    struct hash<mml::Vec<T, 4>>
    {
        size_t operator()(mml::Vec<T, 4> const& vec) const
        {
            return (vec.x * 73856093) ^ (vec.y * 19349663) ^ (vec.z * 83492791) ^ (vec.w ^ 10000019);
        }
    };
}