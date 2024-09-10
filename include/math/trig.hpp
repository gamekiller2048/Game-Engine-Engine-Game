#pragma once
#include <math/common.hpp>

namespace mml
{
	template<typename T>
	T radians(T x)
	{
		return x * ((T)PI / (T)180);
	}

	template<typename T>
	T degrees(T x)
	{
		return x * ((T)180 / (T)PI);
	}

	template<typename T>
	T sin(T x)
	{
		return std::sin(x);
	}

	template<typename T>
	T asin(T x)
	{
		return std::asin(x);
	}

	template<typename T>
	T cos(T x)
	{
		return std::cos(x);
	}

	template<typename T>
	T acos(T x)
	{
		return std::acos(x);
	}

	template<typename T>
	T tan(T x)
	{
		return std::tan(x);
	}

	template<typename T>
	T atan(T x)
	{
		return std::atan(x);
	}

	template<typename T>
	T atan2(T y, T x)
	{
		return std::atan2(y, x);
	}
}