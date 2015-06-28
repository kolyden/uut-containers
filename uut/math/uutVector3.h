#pragma once

namespace uut
{
	class Vector3f
	{
	public:
		union
		{
			struct {
				float x;
				float y;
				float z;
			};
			float m[3];
		};

		Vector3f() {}
		explicit Vector3f(float val)
			: x(val), y(val), z(val) {}
		Vector3f(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z) {}

		Vector3f operator + (const Vector3f& other) const { return Vector3f(x + other.x, y + other.y, z + other.z); }
		Vector3f operator - (const Vector3f& other) const { return Vector3f(x - other.x, y - other.y, z - other.z); }
		Vector3f operator * (const Vector3f& other) const { return Vector3f(x * other.x, y * other.y, z * other.z); }
		Vector3f operator / (const Vector3f& other) const { return Vector3f(x / other.x, y / other.y, z / other.z); }

		Vector3f& operator += (const Vector3f& other) { x += other.x; y += other.y; z += other.z; return *this; }
		Vector3f& operator -= (const Vector3f& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		Vector3f& operator *= (const Vector3f& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		Vector3f& operator /= (const Vector3f& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

		static const Vector3f ZERO;
		static const Vector3f IDENTITY;
	};
}