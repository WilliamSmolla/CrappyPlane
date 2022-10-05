#include "pch.h"
#include "Vec2.h"

Vec2::Vec2()
	: x{ 0 }, y{ 0 } {}

Vec2::Vec2(float x, float y)
	: x{ x }, y{ y } {}

Vec2::~Vec2() {}

float Vec2::DotProduct(const Vec2& vector)
{
	return x*vector.x + y*vector.y;
}

float Vec2::CrossProduct(const Vec2& vector)
{
	return x*vector.y - y*vector.x;
}

float Vec2::Length()
{
	return sqrt(x*x + y*y);
}

float Vec2::Distance(const Vec2& vector)
{
	return sqrt((vector.x - x)* (vector.x - x) +
		(vector.y - y)*(vector.y - y));
}

void Vec2::Normalize()
{
	float length = Length();
	if (length > 0.0f)
	{
		float invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;
	}
}

Vec2& Vec2::operator=(const Vec2& vector)
{
	x = vector.x;
	y = vector.y;

	return *this;
}

Vec2 Vec2::operator+(const Vec2& vector)
{
	return Vec2(x+vector.x, y+vector.y);
}

Vec2 Vec2::operator-(const Vec2& vector)
{
	return Vec2(x-vector.x, y-vector.y);
}

Vec2 Vec2::operator*(const float scalar)
{
	return Vec2(x*scalar, y*scalar);
}

Vec2 Vec2::operator/(const float scalar)
{
	return Vec2(x/scalar, y/scalar);
}

void Vec2::operator+=(const Vec2& vector)
{
	x += vector.x;
	y += vector.y;
}

void Vec2::operator-=(const Vec2& vector)
{
	x -= vector.x;
	y -= vector.y;
}

void Vec2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vec2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
}
