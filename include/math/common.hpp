#pragma once
#include <cmath>
#include <limits>
#include <math/vec.hpp>

namespace mml
{
	constexpr long double PI = 3.141592653589793238462643383279;
	constexpr long double infinity = std::numeric_limits<long double>::infinity();

	template<typename T>
	T min(T x, T y)
	{
		return x < y ? x : y;
	}

	template<typename T>
	T max(T x, T y)
	{
		return x > y ? x : y;
	}

	template<typename T>
	T sqrt(T x)
	{
		return std::sqrt(x);
	}

	template<typename T>
	T ln(T x)
	{
		return std::log(x);
	}

	template<typename T>
	T pow(T base, T power)
	{
		return std::pow(base, power);
	}

	template<typename T>
	T abs(T x)
	{
		return std::abs(x);
	}

	template<typename T>
	T ceil(T x)
	{
		return std::ceil(x);
	}

	template<typename T, size_t N>
	Vec<T, N> ceil(const Vec<T, N>& vec)
	{
		return vec.ceil();
	}

	template<typename T>
	T floor(T x)
	{
		return std::floor(x);
	}

	template<typename T, size_t N>
	Vec<T, N> floor(const Vec<T, N>& vec)
	{
		return vec.floor();
	}

	template<typename T>
	T mod(T x, T y)
	{
		return ((x % y) + y) % y;
	}

	template<typename T, size_t N>
	Vec<T, N> mod(const Vec<T, N>& vec0, const Vec<T, N>& vec1)
	{
		return vec0.mod(vec1);
	}


	template<typename T>
	T sign(T x)
	{
		if(x > 0)
			return 1;
		else if(x < 0)
			return -1;
		return 0;
	}

	template<typename T>
	T fract(T x)
	{
		return x - floor(x);
	}

	template<typename T>
	T bitfieldInsert(T base, T insert, int offset, int bits)
	{
		int mask = ((1 << bits) - 1) << offset;
		return (base & ~mask) | ((insert << offset) & mask);
	}
}