#pragma once
#include <iostream>
#include <math/col.hpp>
#include <math/vec.hpp>

namespace mml
{
    template<typename T>
    class Col<T, 4>
    {
    public:
        union {
            struct {
                T r;
                T g;
                T b;
                T a;
            };
            T data[4];
        };

        Col() = default;
        Col(T value);
        Col(T r, T g, T b, T a);
        Col(T data[4]);
        
        template<typename U>
        explicit Col(const Col<U, 4>& col);

        template<typename U>
        explicit Col(const Vec<U, 4>& vec);


        T* operator&();
        T* operator[](size_t index);
        const T* operator[](size_t index) const;

        template<typename U>
        bool operator==(const Col <U, 4>& vec) const;

        template<typename U>
        Col<T, 4> operator+(const Col<U, 4>& Col) const;
        template<typename U>
        Col<T, 4> operator+(U value) const;
        template<typename U>
        Col<T, 4>& operator+=(const Col<U, 4>& Col);
        template<typename U>
        Col<T, 4>& operator+=(U value);

        template<typename U>
        Col<T, 4> operator-(const Col<U, 4>& Col) const;
        template<typename U>
        Col<T, 4> operator-(U value) const;
        template<typename U>
        Col<T, 4>& operator-=(const Col<U, 4>& Col);
        template<typename U>
        Col<T, 4>& operator-=(U value);

        template<typename U>
        Col<T, 4> operator*(const Col<U, 4>& Col);
        template<typename U>
        Col<T, 4> operator*(U value) const;
        template<typename U>
        Col<T, 4>& operator*=(const Col<U, 4>& Col);
        template<typename U>
        Col<T, 4>& operator*=(U value);

        template<typename U>
        Col<T, 4> operator/(const Col<U, 4>& Col) const;
        template<typename U>
        Col<T, 4> operator/(U value) const;
        template<typename U>
        Col<T, 4>& operator/=(const Col<U, 4>& Col);
        template<typename U>
        Col<T, 4>& operator/=(U value);
    };

    template<typename T>
    Col<T, 4>::Col(T value) :
        r(value), g(value), b(value), a(value) {}

    template<typename T>
    Col<T, 4>::Col(T r, T g, T b, T a) :
        r(r), g(g), b(b), a(a) {}

    template<typename T>
    Col<T, 4>::Col(T data[4]) :
        r(data[0]), g(data[1]), b(data[1]), a(data[3]) {}

    template<typename T>
    template<typename U>
    Col<T, 4>::Col(const Col<U, 4>& col) :
        r((T)col.r), g((T)col.g), b((T)col.b), a((T)col.a) {}

    template<typename T>
    template<typename U>
    Col<T, 4>::Col(const Vec<U, 4>& vec) :
        r((T)vec.x), g((T)vec.y), b((T)vec.z), a((T)vec.w) {}

    
    template<typename T>
    T* Col<T, 4>::operator&()
    {
        return &this->data;
    }

    template<typename T>
    T* Col<T, 4>::operator[](size_t index)
    {
        return this->data[index];
    }

    template<typename T>
    const T* Col<T, 4>::operator[](size_t index) const
    {
        return this->data[index];
    }

    template<typename T>
    template<typename U>
    bool Col<T, 4>::operator==(const Col<U, 4>& col) const
    {
        return this->r == col.r && this->g == col.g && this->b == col.b && this->a == col.a;
    }

    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator+(const Col<U, 4>& Col) const
    {
        return Col<T, 4>(this->r + Col.r, this->g + Col.g, this->b + Col.b, this->a + Col.a);
    }

    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator+(U value) const
    {
        return Col<T, 4>(this->r + value, this->g + value, this->b + value, this->a + value);
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator+=(const Col<U, 4>& Col)
    {
        this->r += Col.r;
        this->g += Col.g;
        this->b += Col.b;
        this->a += Col.a;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator+=(U value)
    {
        this->r += value;
        this->g += value;
        this->b += value;
        this->a += value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator-(const Col<U, 4>& Col) const
    {
        return Col<T, 4>(this->r - Col.r, this->g - Col.g, this->b - Col.b, this->a - Col.a);
    }

    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator-(U value) const
    {
        return Col<T, 4>(this->r - value, this->g - value, this->b - value, this->a - value);
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator-=(const Col<U, 4>& Col)
    {
        this->r -= Col.r;
        this->g -= Col.g;
        this->b -= Col.b;
        this->a -= Col.a;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator-=(U value)
    {
        this->r -= value;
        this->g -= value;
        this->b -= value;
        this->a -= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator*(const Col<U, 4>& Col)
    {
        return Col<T, 4>(this->r * Col.r, this->g * Col.g, this->b * Col.b, this->a * Col.a);
    }

    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator*(U value) const
    {
        return Col<T, 4>(this->r * value, this->g * value, this->b * value, this->a * value);
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator*=(const Col<U, 4>& Col)
    {
        this->r *= Col.r;
        this->g *= Col.g;
        this->b *= Col.b;
        this->a *= Col.a;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator*=(U value)
    {
        this->r *= value;
        this->g *= value;
        this->b *= value;
        this->a *= value;

        return *this;
    }


    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator/(const Col<U, 4>& Col) const
    {
        return Col<T, 4>(this->r / Col.r, this->g / Col.g, this->b / Col.b, this->a / Col.a);
    }

    template<typename T>
    template<typename U>
    Col<T, 4> Col<T, 4>::operator/(U value) const
    {
        return Col<T, 4>(this->r / value, this->g / value, this->b / value, this->a / value);
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator/=(const Col<U, 4>& Col)
    {
        this->r /= Col.r;
        this->g /= Col.g;
        this->b /= Col.b;
        this->a /= Col.a;

        return *this;
    }

    template<typename T>
    template<typename U>
    Col<T, 4>& Col<T, 4>::operator/=(U value)
    {
        this->r /= value;
        this->g /= value;
        this->b /= value;
        this->a /= value;

        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Col<T, 4>& Col)
    {
        return out << '(' << (int)Col.r << ", " << (int)Col.g << ", " << (int)Col.b << ", " << (int)Col.a << ')';
    }
}