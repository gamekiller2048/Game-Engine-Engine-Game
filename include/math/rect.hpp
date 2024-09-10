#pragma once

namespace mml
{
	template<typename T>
	class Rect
	{
	public:
		T x, y, w, h;
	};
}

namespace std
{
	template<typename T>
	struct hash<mml::Rect<T>>
	{
		size_t operator()(const Rect<T>& rect) const
		{
			return (rect.x * 73856093) ^ (rect.y * 19349663) ^ (rect.w * 83492791) ^ (rect.h ^ 10000019);
		}
	};
}