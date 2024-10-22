#pragma once
#include <iostream>
#include <sstream>
#include <math/vec.hpp>
#include <math/mat.hpp>
#include <math/common.hpp>

namespace mml
{
    template<typename T>
    class Vec<T, 2>
    {
    public:
        union {
            struct {
                T x;
                T y;
            };
        
            T data[2];
        };

        Vec() = default;
        Vec(T value);
        Vec(T x, T y);
        Vec(Vec<T, 3> vec);
        Vec(Vec<T, 4> vec);

        static Vec<T, 2> fromArray(const T data[2]);

        template<typename U>
        Vec(const Vec<U, 2>& vec);

        std::string toString() const;

        float length() const;
        Vec<T, 2> floor() const;
        Vec<T, 2> ceil() const;
        Vec<T, 2> mod(const Vec<T, 2>& vec) const;
        Vec<T, 2> normalize() const;

        template<typename U>
        float dot(const Vec<U, 2>& vec) const;

        Vec<T, 2> rotate(T r) const;

        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Vec<U, 2>& vec) const;
        template<typename U>
        bool operator!=(const Vec<U, 2>& vec) const;
        
        template<typename U>
        Vec<T, 2> operator+(const Vec<U, 2>& vec) const;
        template<typename U>
        Vec<T, 2> operator+(U value) const;
        template<typename U>
        Vec<T, 2>& operator+=(const Vec<U, 2>& vec);
        template<typename U>
        Vec<T, 2>& operator+=(U value);

        template<typename U>
        Vec<T, 2> operator-(const Vec<U, 2>& vec) const;
        template<typename U>
        Vec<T, 2> operator-(U value) const;
        Vec<T, 2> operator-() const;
        template<typename U>
        Vec<T, 2>& operator-=(const Vec<U, 2>& vec);
        template<typename U>
        Vec<T, 2>& operator-=(U value);

        template<typename U>
        Vec<T, 2> operator*(const Vec<U, 2>& vec) const;
        template<typename U>
        Vec<T, 2> operator*(U value) const;
        template<typename U>
        Vec<T, 2> operator*(const Mat<U, 2, 2>& mat) const;
        template<typename U>
        Vec<T, 2>& operator*=(const Vec<U, 2>& vec);
        template<typename U>
        Vec<T, 2>& operator*=(U value);

        template<typename U>
        Vec<T, 2> operator/(const Vec<U, 2>& vec) const;
        template<typename U>
        Vec<T, 2> operator/(U value) const;
        template<typename U>
        Vec<T, 2>& operator/=(const Vec<U, 2>& vec);
        template<typename U>
        Vec<T, 2>& operator/=(U value);

        template<typename U>
        Vec<T, 2> operator%(const Vec<U, 2>& vec) const;
        template<typename U>
        Vec<T, 2> operator%(U value) const;
        template<typename U>
        Vec<T, 2>& operator%=(const Vec<U, 2>& vec);
        template<typename U>
        Vec<T, 2>& operator%=(U value);
    };

    template<typename T>
    Vec<T, 2>::Vec(T value) :
        x(value), y(value) {}

    template<typename T>
    Vec<T, 2>::Vec(T x, T y) :
        x(x), y(y) {}

    template<typename T>
    Vec<T, 2>::Vec(Vec<T, 3> vec) :
        x(vec.x), y(vec.y) {}

    template<typename T>
    Vec<T, 2>::Vec(Vec<T, 4> vec) :
        x(vec.x), y(vec.y) {}

    template<typename T>
    Vec<T, 2> Vec<T, 2>::fromArray(const T data[2])
    {
        return Vec<T, 2>(data[0], data[1]);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>::Vec(const Vec<U, 2>& vec) :
        x((T)vec.x), y((T)vec.y) {}


    template<typename T>
    std::string Vec<T, 2>::toString() const
    {
        std::ostringstream oss;
        oss << '(' << this->x << ", " << this->y << ')';
        return oss.str();
    }

    template<typename T>
    float Vec<T, 2>::length() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    template<typename T>
    Vec<T, 2> Vec<T, 2>::floor() const
    {
        return Vec<T, 2>(mml::floor(this->x), mml::floor(this->y));
    }

    template<typename T>
    Vec<T, 2> Vec<T, 2>::ceil() const
    {
        return Vec<T, 2>(mml::ceil(this->x), mml::ceil(this->y));
    }

    template<typename T>
    Vec<T, 2> Vec<T, 2>::mod(const Vec<T, 2>& vec) const
    {
        return Vec<T, 2>(mml::mod(this->x, vec.x), mml::mod(this->y, vec.y));
    }

    template<typename T>
    Vec<T, 2> Vec<T, 2>::normalize() const
    {
        return Vec<T, 2>(this->x, this->y) / this->length();
    }

    template<typename T>
    template<typename U>
    float Vec<T, 2>::dot(const Vec<U, 2>& vec) const
    {
        return this->x * vec.x + this->y * vec.y;
    }
    
    template<typename T>
    Vec<T, 2> Vec<T, 2>::rotate(T r) const
    {
        return Vec<T, 2>(this->x * cos(r) + this->y * sin(r), this->x * -sin(r) + this->y * cos(r));
    }
    

    template<typename T>
    T* Vec<T, 2>::operator&()
    {
        return &this->data[0];
    }

    template<typename T>
    T* Vec<T, 2>::operator[](size_t index)
    {
        return this->data[index];
    }

    template<typename T>
    const T* Vec<T, 2>::operator[](size_t index) const
    {
        return this->data[index];
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 2>::operator==(const Vec<U, 2>& vec) const
    {
        return this->x == vec.x && this->y == vec.y;
    }

    template<typename T>
    template<typename U>
    bool Vec<T, 2>::operator!=(const Vec<U, 2>& vec) const
    {
        return this->x != vec.x || this->y != vec.y;
    }


    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator+(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(this->x + vec.x, this->y + vec.y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator+(U value) const
    {
        return Vec<T, 2>(this->x + value, this->y + value);
    }

    template<typename T, typename U>
    Vec<T, 2> operator+(U value, Vec<T, 2> vec)
    {
        return Vec<T, 2>(vec.x + value, vec.y + value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator+=(const Vec<U, 2>& vec)
    {
        this->x += vec.x;
        this->y += vec.y;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator+=(U value)
    {
        this->x += value;
        this->y += value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator-(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(this->x - vec.x, this->y - vec.y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator-(U value) const
    {
        return Vec<T, 2>(this->x - value, this->y - value);
    }

    template<typename T, typename U>
    Vec<T, 2> operator-(U value, Vec<T, 2> vec)
    {
        return Vec<T, 2>(vec.x - value, vec.y - value);
    }

    template<typename T>
    Vec<T, 2> Vec<T, 2>::operator-() const
    {
        return Vec<T, 2>(-this->x, -this->y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator-=(const Vec<U, 2>& vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator-=(U value)
    {
        this->x -= value;
        this->y -= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator*(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(this->x * vec.x, this->y * vec.y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator*(U value) const
    {
        return Vec<T, 2>(this->x * value, this->y * value);
    }

    template<typename T, typename U>
    Vec<T, 2> operator*(U value, Vec<T, 2> vec)
    {
        return Vec<T, 2>(vec.x * value, vec.y * value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator*(const Mat<U, 2, 2>& mat) const
    {
        return Vec<T, 2>(
            mat[0][0] * this->x + mat[1][0] * this->y,
            mat[0][1] * this->x + mat[1][1] * this->y
        );
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator*=(const Vec<U, 2>& vec)
    {
        this->x *= vec.x;
        this->y *= vec.y;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator*=(U value)
    {
        this->x *= value;
        this->y *= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator/(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(this->x / vec.x, this->y / vec.y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator/(U value) const
    {
        return Vec<T, 2>(this->x / value, this->y / value);
    }

    template<typename T, typename U>
    Vec<T, 2> operator/(U value, Vec<T, 2> vec)
    {
        return Vec<T, 2>(vec.x / value, vec.y / value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator/=(const Vec<U, 2>& vec)
    {
        this->x /= vec.x;
        this->y /= vec.y;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator/=(U value)
    {
        this->x /= value;
        this->y /= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator%(const Vec<U, 2>& vec) const
    {
        return Vec<T, 2>(this->x % vec.x, this->y % vec.y);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2> Vec<T, 2>::operator%(U value) const
    {
        return Vec<T, 2>(this->x % value, this->y % value);
    }

    template<typename T, typename U>
    Vec<T, 2> operator%(U value, Vec<T, 2> vec)
    {
        return Vec<T, 2>(vec.x % value, vec.y % value);
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator%=(const Vec<U, 2>& vec)
    {
        this->x %= vec.x;
        this->y %= vec.y;

        return *this;
    }

    template<typename T>
    template<typename U>
    Vec<T, 2>& Vec<T, 2>::operator%=(U value)
    {
        this->x %= value;
        this->y %= value;

        return *this;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vec<T, 2>& vec)
    {
        return vec.toString();
    }
}

namespace std
{
    template<typename T>
    struct hash<mml::Vec<T, 2>>
    {
        size_t operator()(mml::Vec<T, 2> const& vec) const
        {
            return (vec.x * 73856093) ^ (vec.y * 19349663);
        }
    };
}
