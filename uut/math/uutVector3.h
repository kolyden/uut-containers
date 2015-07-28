#pragma once
#include "uutMath.h"

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

		Vector3f operator * (float val) const { return Vector3f(x * val, y * val, z * val); }
		Vector3f operator / (float val) const { return Vector3f(x / val, y / val, z / val); }

		Vector3f& operator += (const Vector3f& other) { x += other.x; y += other.y; z += other.z; return *this; }
		Vector3f& operator -= (const Vector3f& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		Vector3f& operator *= (const Vector3f& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		Vector3f& operator /= (const Vector3f& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

		Vector3f operator-() const { return Vector3f(-x, -y, -z); }
		Vector3f operator+() const { return *this; }

		void Normalize()
		{
			float lenSquared = LengthSquared();
			if (!Math::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
			{
				float invLen = 1.0f / sqrtf(lenSquared);
				x *= invLen;
				y *= invLen;
				z *= invLen;
			}
		}

		Vector3f Normalized() const
		{
			float lenSquared = LengthSquared();
			if (!Math::Equals(lenSquared, 1.0f) && lenSquared > 0.0f)
			{
				float invLen = 1.0f / sqrtf(lenSquared);
				return *this * invLen;
			}
			else
				return *this;
		}

		float Length() const { return sqrtf(x * x + y * y + z * z); }
		float LengthSquared() const { return x * x + y * y + z * z; }

		static const Vector3f ZERO;
		static const Vector3f ONE;
		static const Vector3f AXIS_X;
		static const Vector3f AXIS_Y;
		static const Vector3f AXIS_Z;
		static const Vector3f AXIS_XY;
		static const Vector3f AXIS_XZ;
		static const Vector3f AXIS_YZ;
	};
}