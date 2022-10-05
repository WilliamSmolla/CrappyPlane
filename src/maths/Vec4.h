#pragma once
struct Vec4
{
	float x, y, z, w;

	Vec4();
	Vec4(float x, float y, float z, float w);
	~Vec4();

	Vec4& operator=(const Vec4& vector);
	Vec4 operator+(const Vec4& vector);
	Vec4 operator-(const Vec4& vector);
	Vec4 operator*(const float scalar);
	Vec4 operator/(const float scalar);
	void operator+=(const Vec4& vector);
	void operator-=(const Vec4& vector);
	void operator*=(const float scalar);
	void operator/=(const float scalar);
};

