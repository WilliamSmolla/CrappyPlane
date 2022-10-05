#pragma once
 struct Vec3
{
	 float x, y, z;

	 Vec3();
	 Vec3(float x, float y, float z);
	 ~Vec3();

	 float DotProduct(const Vec3& vector);
	 Vec3 CrossProduct(const Vec3& vector);
	 float Length();
	 float Distance(const Vec3& vector);
	 void Normalize();

	 Vec3& operator=(const Vec3& vector);
	 Vec3 operator+(const Vec3& vector);
	 Vec3 operator-(const Vec3& vector);
	 Vec3 operator*(const float scalar);
	 Vec3 operator/(const float scalar);
	 void operator+=(const Vec3& vector);
	 void operator-=(const Vec3& vector);
	 void operator*=(const float scalar);
	 void operator/=(const float scalar);
};

