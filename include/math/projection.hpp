#pragma once
#include <math/mat.hpp>
#include <math/vec.hpp>
#include <math/transform.hpp>

namespace mml
{
	template<typename T>
	Mat<T, 4, 4> perspective(T fov, T far, T near, T aspect)
	{
		T a = std::tan(fov / 2);

		return Mat<T, 4, 4>(1 / (aspect * a), 0, 0, 0,
							0, 1 / a, 0, 0,
							0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
							0, 0, -1, 0);
	}

	template<typename T>
	Mat<T, 4, 4> orthographic(T left, T right, T top, T bottom, T near, T far)
	{
		return Mat<T, 4, 4>(2 / (right - left), 0, 0, -(right + left) / (right - left),
							0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
							0, 0, -2 / (far - near), -(far + near) / (far - near),
							0, 0, 0, 1);
	}

	template<typename T>
	Mat<T, 4, 4> lookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
	{
		Vec<T, 3> dir = normalize(center - eye);
		Vec<T, 3> aUp = normalize(up);
		Vec<T, 3> right = normalize(dir.cross(aUp));
		aUp = right.cross(dir);

		return Mat<T, 4, 4>(
			right.x, right.y, right.z, -right.dot(eye),
			aUp.x, aUp.y, aUp.z, -aUp.dot(eye),
			-dir.x, -dir.y, -dir.z, dir.dot(eye),
			0, 0, 0, 1
		);
	}
}