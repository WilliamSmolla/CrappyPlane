#include "pch.h"
#include "Vec3.h"

Vec3::Vec3()
    : x{ 0 }, y{ 0 }, z{ 0 } {}

Vec3::Vec3(float x, float y, float z)
    : x{ x }, y{ y }, z{ z } {}

Vec3::~Vec3() {}

float Vec3::DotProduct(const Vec3& vector)
{
    return x*vector.x + y*vector.y, z*vector.z;
}

Vec3 Vec3::CrossProduct(const Vec3& vector)
{
    return Vec3(y * vector.z - z * vector.y,
        z * vector.x - x * vector.z,
        x * vector.y - y * vector.x);
}

float Vec3::Length()
{
    return sqrt(x*x + y*y + z*z);
}

float Vec3::Distance(const Vec3& vector)
{
    return sqrt((x-vector.x) * (x - vector.x) +
        (y - vector.y) * (y - vector.y) +
        (z - vector.z) * (z - vector.z));
}

void Vec3::Normalize()
{
    float length = Length();
    if (length > 0.0f)
    {
        float invLength = 1.0f / length;
        x *= invLength;
        y *= invLength;
        z *= invLength;
    }
}

Vec3& Vec3::operator=(const Vec3& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;

    return *this;
}

Vec3 Vec3::operator+(const Vec3& vector)
{
    return Vec3(x + vector.x, y + vector.y, z + vector.z);
}

Vec3 Vec3::operator-(const Vec3& vector)
{
    return Vec3(x - vector.x, y - vector.y, z - vector.z);
}

Vec3 Vec3::operator*(const float scalar)
{
    return Vec3(x*scalar, y*scalar, z*scalar);
}

Vec3 Vec3::operator/(const float scalar)
{
    return Vec3(x / scalar, y / scalar, z / scalar);
}

void Vec3::operator+=(const Vec3& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

void Vec3::operator-=(const Vec3& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
}

void Vec3::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z += scalar;
}

void Vec3::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
}
