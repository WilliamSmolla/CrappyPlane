#pragma once
struct Vec2
{
	float x, y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();

	float DotProduct(const Vec2& vector);
	float CrossProduct(const Vec2& vector);
	float Length();
	float Distance(const Vec2& vector);
	void Normalize();

	Vec2& operator=(const Vec2& vector);
	Vec2 operator+(const Vec2& vector);
	Vec2 operator-(const Vec2& vector);
	Vec2 operator*(const float scalar);
	Vec2 operator/(const float scalar);
	void operator+=(const Vec2& vector);
	void operator-=(const Vec2& vector);
	void operator*=(const float scalar);
	void operator/=(const float scalar);
};

