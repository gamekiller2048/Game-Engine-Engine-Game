#pragma once
#include <iostream>
#include <sstream>
#include <math/vec.hpp>
#include <math/col.hpp>
#include <math/mat.hpp>
#include <math/common.hpp>

namespace mml
{
    template<typename T>
    class Vec<T, 3>
    {
    public:
        union {
            struct {
                T x;
                T y;
                T z;
            };
            T data[3];
        };

        Vec() = default;
        constexpr Vec(T value);
        constexpr Vec(T x, T y, T z);
        Vec(Vec<T, 4> vec);

        static Vec<T, 3> fromArray(const T data[3]);
        
        template<typename U>
        Vec(const Vec<U, 3>& vec);

        template<typename U>
        explicit Vec(const Col<U, 3>& col);

        std::string toString() const;

        float length() const;
        Vec<T, 3> floor() const;
        Vec<T, 3> ceil() const;
        Vec<T, 3> mod(const Vec<T, 3>& vec) const;
        Vec<T, 3> normalize() const;

        template<typename U>
        float dot(const Vec<U, 3>& vec) const;

        template<typename U>
        Vec<T, 3> cross(const Vec<U, 3>& vec) const;

        Vec<T, 3> rotate(const Vec<T, 3>& vec) const;

        T* operator&();
        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        template<typename U>
        bool operator==(const Vec<U, 3>& vec) const;
        template<typename U>
        bool operator!=(const Vec<U, 3>& vec) const;

        template<typename U>
        Vec<T, 3> operator+(const Vec<U, 3>& vec) const;
        template<typename U>
        Vec<T, 3> operator+(U value) const;
        template<typename U>
        Vec<T, 3>& operator+=(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3>& operator+=(U value);

        template<typename U>
        Vec<T, 3> operator-(const Vec<U, 3>& vec) const;
        template<typename U>
        Vec<T, 3> operator-(U value) const;
        Vec<T, 3> operator-() const;
        template<typename U>
        Vec<T, 3>& operator-=(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3>& operator-=(U value);

        template<typename U>
        Vec<T, 3> operator*(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3> operator*(U value) const;
        template<typename U>
        Vec<T, 3> operator*(const Mat<U, 3, 3>& mat) const;
        template<typename U>
        Vec<T, 3>& operator*=(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3>& operator*=(U value);

        template<typename U>
        Vec<T, 3> operator/(const Vec<U, 3>& vec) const;
        template<typename U>
        Vec<T, 3> operator/(U value) const;
        template<typename U>
        Vec<T, 3>& operator/=(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3>& operator/=(U value);

        template<typename U>
        Vec<T, 3> operator%(const Vec<U, 3>& vec) const;
        template<typename U>
        Vec<T, 3> operator%(U value) const;
        template<typename U>
        Vec<T, 3>& operator%=(const Vec<U, 3>& vec);
        template<typename U>
        Vec<T, 3>& operator%=(U value);
    };

    template<typename T>
    constexpr Vec<T, 3>::Vec(T value) :
        x(value), y(value), z(value) {}

    template<typename T>
    constexpr Vec<T, 3>::Vec(T x, T y, T z) :
        x(x), y(y), z(z) {}

    template<typename T>
    Vec<T, 3>::Vec(Vec<T, 4> vec) :
        x(vec.x), y(vec.y), z(vec.z) {}

    template<typename T>
    Vec<T, 3> Vec<T, 3>::fromArray(const T data[3])
    {
        return Vec<T, 3>(data[0], data[1], data[2]);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>::Vec(const Vec<U, 3>& vec) :
        x((T)vec.x), y((T)vec.y), z((T)vec.z) {}

    template<typename T>
    template<typename U>
    Vec<T, 3>::Vec(const Col<U, 3>& col) :
        x((T)col.r), y((T)col.g), z((T)col.b) {}


    template<typename T>
    std::string Vec<T, 3>::toString() const
    {
        std::ostringstream oss;
        oss << '(' << this->x << ", " << this->y << ", " << this->z << ')';
        return oss.str();
    }

    template<typename T>
    float Vec<T, 3>::length() const
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::floor() const
    {
        return Vec<T, 3>(mml::floor(x), mml::floor(y), mml::floor(z));
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::ceil() const
    {
        return Vec<T, 3>(mml::ceil(this->x), mml::ceil(this->y), mml::ceil(this->z));
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::mod(const Vec<T, 3>& vec) const
    {
        return Vec<T, 3>(mml::mod(this->x, vec.x), mml::mod(this->y, vec.y), mml::mod(this->z, vec.z));
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::normalize() const
    {
        return Vec<T, 3>(this->x, this->y, this->z) / this->length();
    }

    template<typename T>
    template<typename U>
    float Vec<T, 3>::dot(const Vec<U, 3>& vec) const
    {
        return this->x * vec.x + this->y * vec.y + this->z * vec.z;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::cross(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::rotate(const Vec<T, 3>& vec) const
    {
        Mat<T, 3, 3> rx(
            1, 0, 0,
            0, cos(vec.x), -sin(vec.x),
            0, sin(vec.x), cos(vec.x)
        );

        Mat<T, 3, 3> ry(
            cos(vec.y), 0, sin(vec.y),
            0, 1, 0,
            -sin(vec.y), 0, cos(vec.y)
        );

        Mat<T, 3, 3> rz(
            cos(vec.z), -sin(vec.z), 0,
            sin(vec.z), cos(vec.z), 0,
            0, 0, 1
        );

        return Vec<T, 3>(this->x, this->y, this->z) * rx * ry * rz;
    }


    template<typename T>
    T* Vec<T, 3>::operator&()
    {
        return &this->data[0];
    }

    template<typename T>
    T& Vec<T, 3>::operator[](size_t index)
    {
        return this->data[index];
    }

    template<typename T>
    const T& Vec<T, 3>::operator[](size_t index) const
    {
        return this->data[index];
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 3>::operator==(const Vec<U, 3>& vec) const
    {
        return this->x == vec.x && this->y == vec.y && this->z == vec.z;
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 3>::operator!=(const Vec<U, 3>& vec) const
    {
        return this->x != vec.x || this->y != vec.y || this->z != vec.z;
    }


    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator+(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator+(U value) const
    {
        return Vec<T, 3>(this->x + value, this->y + value, this->z + value);
    }

    template<typename T, typename U>
    Vec<T, 3> operator+(U value, Vec<T, 3> vec)
    {
        return Vec<T, 3>(vec.x + value, vec.y + value, vec.z + value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator+=(const Vec<U, 3>& vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        this->z += vec.z;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator+=(U value)
    {
        this->x += value;
        this->y += value;
        this->z += value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator-(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(this->x - vec.x, this->y - vec.y, this->z - vec.z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator-(U value) const
    {
        return Vec<T, 3>(this->x - value, this->y - value, this->z - value);
    }

    template<typename T, typename U>
    Vec<T, 3> operator-(U value, Vec<T, 3> vec)
    {
        return Vec<T, 3>(vec.x - value, vec.y - value, vec.z - value);
    }

    template<typename T>
    Vec<T, 3> Vec<T, 3>::operator-() const
    {
        return Vec<T, 3>(-this->x, -this->y, -this->z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator-=(const Vec<U, 3>& vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;
        this->z -= vec.z;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator-=(U value)
    {
        this->x -= value;
        this->y -= value;
        this->z -= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator*(const Vec<U, 3>& vec)
    {
        return Vec<T, 3>(this->x * vec.x, this->y * vec.y, this->z * vec.z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator*(U value) const
    {
        return Vec<T, 3>(this->x * value, this->y * value, this->z * value);
    }

    template<typename T, typename U>
    Vec<T, 3> operator*(U value, Vec<T, 3> vec)
    {
        return Vec<T, 3>(vec.x * value, vec.y * value, vec.z * value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator*(const Mat<U, 3, 3>& mat) const
    {
        return Vec<T, 3>(
            mat[0][0] * this->x + mat[1][0] * this->y + mat[2][0] * this->z,
            mat[0][1] * this->x + mat[1][1] * this->y + mat[2][1] * this->z,
            mat[0][2] * this->x + mat[1][2] * this->y + mat[2][2] * this->z
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator*=(const Vec<U, 3>& vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;
        this->z *= vec.z;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator*=(U value)
    {
        this->x *= value;
        this->y *= value;
        this->z *= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator/(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(this->x / vec.x, this->y / vec.y, this->z / vec.z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator/(U value) const
    {
        return Vec<T, 3>(this->x / value, this->y / value, this->z / value);
    }

    template<typename T, typename U>
    Vec<T, 3> operator/(U value, Vec<T, 3> vec)
    {
        return Vec<T, 3>(vec.x / value, vec.y / value, vec.z / value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator/=(const Vec<U, 3>& vec)
    {
        this->x /= vec.x;
        this->y /= vec.y;
        this->z /= vec.z;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator/=(U value)
    {
        this->x /= value;
        this->y /= value;
        this->z /= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator%(const Vec<U, 3>& vec) const
    {
        return Vec<T, 3>(this->x % vec.x, this->y % vec.y, this->z % vec.z);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3> Vec<T, 3>::operator%(U value) const
    {
        return Vec<T, 3>(this->x % value, this->y % value, this->z % value);
    }

    template<typename T, typename U>
    Vec<T, 3> operator%(U value, Vec<T, 3> vec)
    {
        return Vec<T, 3>(vec.x % value, vec.y % value, vec.z % value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator%=(const Vec<U, 3>& vec)
    {
        this->x %= vec.x;
        this->y %= vec.y;
        this->z %= vec.z;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 3>& Vec<T, 3>::operator%=(U value)
    {
        this->x %= value;
        this->y %= value;
        this->z %= value;

        return *this;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vec<T, 3>& vec)
    {
        return out << vec.toString();
    }
}

namespace std
{
    template<typename T>
    struct hash<mml::Vec<T, 3>>
    {
        size_t operator()(mml::Vec<T, 3> const& vec) const
        {
            return (vec.x * 73856093) ^ (vec.y * 19349663) ^ (vec.z * 83492791);
        }
    };
}
