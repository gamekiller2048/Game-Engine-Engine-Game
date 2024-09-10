#pragma once
#include <iostream>
#include <math/col.hpp>
#include <math/vec.hpp>

namespace mml
{
    template<typename T>
    class Col<T, 3>
    {
    public:
        union {
            struct {
                T r;
                T g;
                T b;
            };
            T data[3];
        };

        Col() = default;
        Col(T value);
        Col(T r, T g, T b);
        Col(T data[3]);

        template<typename U>
        explicit Col(const Col<U, 3>& col);

        template<typename U>
        explicit Col(const Vec<U, 3>& vec);

        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Col<U, 3>& col) const;

        template<typename U>
        Col<T, 3> operator+(const Col<U, 3>& Col) const;
        template<typename U>
        Col<T, 3> operator+(U value) const;
        template<typename U>
        Col<T, 3>& operator+=(const Col<U, 3>& Col);
        template<typename U>
        Col<T, 3>& operator+=(U value);

        template<typename U>
        Col<T, 3> operator-(const Col<U, 3>& Col) const;
        template<typename U>
        Col<T, 3> operator-(U value) const;
        template<typename U>
        Col<T, 3>& operator-=(const Col<U, 3>& Col);
        template<typename U>
        Col<T, 3>& operator-=(U value);

        template<typename U>
        Col<T, 3> operator*(const Col<U, 3>& Col);
        template<typename U>
        Col<T, 3> operator*(U value) const;
        template<typename U>
        Col<T, 3>& operator*=(const Col<U, 3>& Col);
        template<typename U>
        Col<T, 3>& operator*=(U value);

        template<typename U>
        Col<T, 3> operator/(const Col<U, 3>& Col) const;
        template<typename U>
        Col<T, 3> operator/(U value) const;
        template<typename U>
        Col<T, 3>& operator/=(const Col<U, 3>& Col);
        template<typename U>
        Col<T, 3>& operator/=(U value);
    };

    template<typename T>
    Col<T, 3>::Col(T value) :
        r(value), g(value), b(value) {}

    template<typename T>
    Col<T, 3>::Col(T r, T g, T b) :
        r(r), g(g), b(b) {}

    template<typename T>
    Col<T, 3>::Col(T data[3]) :
        r(data[0]), g(data[1]), b(data[2]) {}

    template<typename T>
    template<typename U>
    Col<T, 3>::Col(const Col<U, 3>& col) :
        r((T)col.r), g((T)col.g), b((T)col.b) {}

    template<typename T>
    template<typename U>
    Col<T, 3>::Col(const Vec<U, 3>& vec) :
        r((T)vec.x), g((T)vec.y), b((T)vec.z) {}


    template<typename T>
        T* Col<T, 3>::operator&()
    {
        return &this->data;
    }

    template<typename T>
    T* Col<T, 3>::operator[](size_t index)
    {
        return this->data[index];
    }

    template<typename T>
    const T* Col<T, 3>::operator[](size_t index) const
    {
        return this->data[index];
    }

    template<typename T>
    template<typename U>
    bool Col<T, 3>::operator==(const Col<U, 3>& col) const
    {
        return this->r == col.r && this->g == col.g && this->b == col.b;
    }

    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator+(const Col<U, 3>& Col) const
    {
        return Col<T, 3>(this->r + Col.r, this->g + Col.g, this->b + Col.b);
    }

    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator+(U value) const
    {
        return Col<T, 3>(this->r + value, this->g + value, this->b + value);
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator+=(const Col<U, 3>& Col)
    {
        this->r += Col.r;
        this->g += Col.g;
        this->b += Col.b;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator+=(U value)
    {
        this->r += value;
        this->g += value;
        this->b += value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator-(const Col<U, 3>& Col) const
    {
        return Col<T, 3>(this->r - Col.r, this->g - Col.g, this->b - Col.b);
    }

    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator-(U value) const
    {
        return Col<T, 3>(this->r - value, this->g - value, this->b - value);
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator-=(const Col<U, 3>& Col)
    {
        this->r -= Col.r;
        this->g -= Col.g;
        this->b -= Col.b;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator-=(U value)
    {
        this->r -= value;
        this->g -= value;
        this->b -= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator*(const Col<U, 3>& Col)
    {
        return Col<T, 3>(this->r * Col.r, this->g * Col.g, this->b * Col.b);
    }

    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator*(U value) const
    {
        return Col<T, 3>(this->r * value, this->g * value, this->b * value);
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator*=(const Col<U, 3>& Col)
    {
        this->r *= Col.r;
        this->g *= Col.g;
        this->b *= Col.b;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator*=(U value)
    {
        this->r *= value;
        this->g *= value;
        this->b *= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator/(const Col<U, 3>& Col) const
    {
        return Col<T, 3>(this->r / Col.r, this->g / Col.g, this->b / Col.b);
    }

    template<typename T>
    template<typename U>
    Col<T, 3> Col<T, 3>::operator/(U value) const
    {
        return Col<T, 3>(this->r / value, this->g / value, this->b / value);
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator/=(const Col<U, 3>& Col)
    {
        this->r /= Col.r;
        this->g /= Col.g;
        this->b /= Col.b;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 3>& Col<T, 3>::operator/=(U value)
    {
        this->r /= value;
        this->g /= value;
        this->b /= value;

        return *this;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Col<T, 3>& Col)
    {
        return out << '(' << Col.r << ", " << Col.g << ", " << Col.b << ')';
    }
}
