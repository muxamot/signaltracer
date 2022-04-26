#pragma once

#include "vector.hpp"

namespace math 
{
	struct Quaternion
	{
		float x, y, z, w;

		Quaternion(float _x, float _y, float _z, float _w);

		void Normalize();

		Quaternion Conjugate();
	};

	Quaternion operator*(const Quaternion& l, const Quaternion& r);

	Quaternion operator*(const Quaternion& q, const Vector3f& v);
}