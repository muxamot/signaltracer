#pragma once

#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

namespace math
{

	struct Vector2i
	{
		int x;
		int y;
	};

	struct Vector2f
	{
		float x;
		float y;

		Vector2f()
		{
		}

		Vector2f(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
	};

	struct Vector3f
	{
		float x;
		float y;
		float z;

		Vector3f()
		{
		}

		Vector3f(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		Vector3f& operator+=(const Vector3f& r)
		{
			x += r.x;
			y += r.y;
			z += r.z;

			return *this;
		}

		Vector3f& operator-=(const Vector3f& r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;

			return *this;
		}

		Vector3f& operator*=(float f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		Vector3f Cross(const Vector3f& v) const;

		Vector3f& Normalize();

		void Rotate(double Angle, const Vector3f& Axis);

		void Print() const
		{
			printf("(%.02f, %.02f, %.02f", x, y, z);
		}
	};

	inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
	{
		Vector3f Ret(l.x + r.x,
			l.y + r.y,
			l.z + r.z);

		return Ret;
	}

	inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
	{
		Vector3f Ret(l.x - r.x,
			l.y - r.y,
			l.z - r.z);

		return Ret;
	}

	inline Vector3f operator*(const Vector3f& l, float f)
	{
		Vector3f Ret(l.x * f,
					 l.y * f,
					 l.z * f);

		return Ret;
	}

	struct Vector4f
	{
		float x;
		float y;
		float z;
		float w;

		Vector4f()
		{
		}

		Vector4f(float _x, float _y, float _z, float _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		Vector4f& operator+=(const Vector4f& r)
		{
			x += r.x;
			y += r.y;
			z += r.z;
			w += r.w;

			return *this;
		}

		Vector4f& operator-=(const Vector4f& r)
		{
			x -= r.x;
			y -= r.y;
			z -= r.z;
			w -= r.w;

			return *this;
		}

		Vector4f& operator*=(float f)
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;

			return *this;
		}

		void Print() const
		{
			printf("(%.02f, %.02f, %.02f, %.02f", x, y, z, w);
		}
	};

	inline Vector4f operator+(const Vector4f& l, const Vector4f& r)
	{
		Vector4f Ret(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);

		return Ret;
	}

	inline Vector4f operator-(const Vector4f& l, const Vector4f& r)
	{
		Vector4f Ret(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);

		return Ret;
	}

	inline Vector4f operator*(const Vector4f& l, float f)
	{
		Vector4f Ret(l.x * f, l.y * f, l.z * f, l.w * f);

		return Ret;
	}

}