#pragma once

namespace uut
{
	template<class T>
	class BaseVector2
	{
	public:
		union
		{
			T m[2];
			struct
			{
				T x;
				T y;
			};
		};

		BaseVector2() {}
		explicit BaseVector2(T val)
			: x(val), y(val) {}
		BaseVector2(T _x, T _y)
			: x(_x), y(_y) {}

		BaseVector2 operator + (const BaseVector2& other) const { return BaseVector2(x + other.x, y + other.y); }
		BaseVector2 operator - (const BaseVector2& other) const { return BaseVector2(x - other.x, y - other.y); }
		BaseVector2 operator * (const BaseVector2& other) const { return BaseVector2(x * other.x, y * other.y); }
		BaseVector2 operator / (const BaseVector2& other) const { return BaseVector2(x / other.x, y / other.y); }

		BaseVector2& operator += (const BaseVector2& other) { x += other.x; y += other.y; return *this; }
		BaseVector2& operator -= (const BaseVector2& other) { x -= other.x; y -= other.y; return *this; }
		BaseVector2& operator *= (const BaseVector2& other) { x *= other.x; y *= other.y; return *this; }
		BaseVector2& operator /= (const BaseVector2& other) { x /= other.x; y /= other.y; return *this; }
	};

	typedef BaseVector2<float> Vector2;
	typedef BaseVector2<int> IntVector2;
}