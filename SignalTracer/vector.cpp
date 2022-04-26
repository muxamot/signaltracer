#include "vector.hpp"
#include "quaternion.hpp"


namespace math
{
	Vector3f Vector3f::Cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f& Vector3f::Normalize()
	{
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	void Vector3f::Rotate(double Angle, const Vector3f& Axe)
	{
		const double SinHalfAngle = sinf(ToRadian(Angle / 2));
		const double CosHalfAngle = cosf(ToRadian(Angle / 2));

		const double Rx = Axe.x * SinHalfAngle;
		const double Ry = Axe.y * SinHalfAngle;
		const double Rz = Axe.z * SinHalfAngle;
		const double Rw = CosHalfAngle;
		Quaternion RotationQ(Rx, Ry, Rz, Rw);

		Quaternion ConjugateQ = RotationQ.Conjugate();

		Quaternion W = RotationQ * (*this) * ConjugateQ;

		x = W.x;
		y = W.y;
		z = W.z;
	}
}