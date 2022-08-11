#include "matrix.hpp"

namespace math
{

void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
{
    m[0][0] = ScaleX;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = ScaleY;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = ScaleZ;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
{
    Matrix4f rx, ry, rz;

    const float x = ToRadian(RotateX);
    const float y = ToRadian(RotateY);
    const float z = ToRadian(RotateZ);

    rx.m[0][0] = 1.0f;
    rx.m[0][1] = 0.0f;
    rx.m[0][2] = 0.0f;
    rx.m[0][3] = 0.0f;
    rx.m[1][0] = 0.0f;
    rx.m[1][1] = cosf(x);
    rx.m[1][2] = -sinf(x);
    rx.m[1][3] = 0.0f;
    rx.m[2][0] = 0.0f;
    rx.m[2][1] = sinf(x);
    rx.m[2][2] = cosf(x);
    rx.m[2][3] = 0.0f;
    rx.m[3][0] = 0.0f;
    rx.m[3][1] = 0.0f;
    rx.m[3][2] = 0.0f;
    rx.m[3][3] = 1.0f;

    ry.m[0][0] = cosf(y);
    ry.m[0][1] = 0.0f;
    ry.m[0][2] = -sinf(y);
    ry.m[0][3] = 0.0f;
    ry.m[1][0] = 0.0f;
    ry.m[1][1] = 1.0f;
    ry.m[1][2] = 0.0f;
    ry.m[1][3] = 0.0f;
    ry.m[2][0] = sinf(y);
    ry.m[2][1] = 0.0f;
    ry.m[2][2] = cosf(y);
    ry.m[2][3] = 0.0f;
    ry.m[3][0] = 0.0f;
    ry.m[3][1] = 0.0f;
    ry.m[3][2] = 0.0f;
    ry.m[3][3] = 1.0f;

    rz.m[0][0] = cosf(z);
    rz.m[0][1] = -sinf(z);
    rz.m[0][2] = 0.0f;
    rz.m[0][3] = 0.0f;
    rz.m[1][0] = sinf(z);
    rz.m[1][1] = cosf(z);
    rz.m[1][2] = 0.0f;
    rz.m[1][3] = 0.0f;
    rz.m[2][0] = 0.0f;
    rz.m[2][1] = 0.0f;
    rz.m[2][2] = 1.0f;
    rz.m[2][3] = 0.0f;
    rz.m[3][0] = 0.0f;
    rz.m[3][1] = 0.0f;
    rz.m[3][2] = 0.0f;
    rz.m[3][3] = 1.0f;

    *this = rz * ry * rx;
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = x;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = y;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[2][3] = z;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
{
    Vector3f N = Target;
    N.Normalize();
    Vector3f U = Up;
    U.Normalize();
    U = U.Cross(N);
    Vector3f V = N.Cross(U);

    m[0][0] = U.x;
    m[0][1] = U.y;
    m[0][2] = U.z;
    m[0][3] = 0.0f;
    m[1][0] = V.x;
    m[1][1] = V.y;
    m[1][2] = V.z;
    m[1][3] = 0.0f;
    m[2][0] = N.x;
    m[2][1] = N.y;
    m[2][2] = N.z;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void Matrix4f::InitPersProjTransform(float FOV, float Width, float Height, float zNear, float zFar)
{
    const float ar = Width / Height;
    const float zRange = zNear - zFar;
    const float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));

    m[0][0] = 1.0f / (tanHalfFOV * ar);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHalfFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (-zNear - zFar) / zRange;
    m[2][3] = 2.0f * zFar * zNear / zRange;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 1.0f;
    m[3][3] = 0.0;
}

} // namespace math