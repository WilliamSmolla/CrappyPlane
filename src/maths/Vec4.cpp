#include "pch.h"
#include "Vec4.h"

Vec4::Vec4()
    : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }{}

Vec4::Vec4(float x, float y, float z, float w)
    : x{ x }, y{ y }, z{ z }, w{ w }{}

Vec4::~Vec4(){}

Vec4& Vec4::operator=(const Vec4& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;

    return *this;
}

Vec4 Vec4::operator+(const Vec4& vector)
{
    return Vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

Vec4 Vec4::operator-(const Vec4& vector)
{
    return Vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

Vec4 Vec4::operator*(const float scalar)
{
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vec4 Vec4::operator/(const float scalar)
{
    return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

void Vec4::operator+=(const Vec4& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    w += vector.w;
}

void Vec4::operator-=(const Vec4& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    w -= vector.w;
}

void Vec4::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}

void Vec4::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
}
