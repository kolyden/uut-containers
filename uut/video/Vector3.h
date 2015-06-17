#pragma once

namespace uut
{
	template<class T>
	class BaseVector3
	{
	public:
		union
		{
			float m[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};

		BaseVector3() {}
		explicit BaseVector3(float val)
			: x(val), y(val), z(val) {}
		BaseVector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z) {}

		BaseVector3 operator + (const BaseVector3& other) const { return BaseVector3(x + other.x, y + other.y, z + other.z); }
		BaseVector3 operator - (const BaseVector3& other) const { return BaseVector3(x - other.x, y - other.y, z - other.z); }
		BaseVector3 operator * (const BaseVector3& other) const { return BaseVector3(x * other.x, y * other.y, z * other.z); }
		BaseVector3 operator / (const BaseVector3& other) const { return BaseVector3(x / other.x, y / other.y, z / other.z); }

		BaseVector3& operator += (const BaseVector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
		BaseVector3& operator -= (const BaseVector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		BaseVector3& operator *= (const BaseVector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		BaseVector3& operator /= (const BaseVector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	};

	typedef BaseVector3<float> Vector3;
	typedef BaseVector3<int> IntVector3;
}