#pragma once
#include "core/uutDefs.h"

namespace uut
{
	class Vector2f
	{
	public:
		union
		{
			float m[2];
			struct
			{
				float x;
				float y;
			};
		};

		Vector2f() {}
		explicit Vector2f(float val) : x(val), y(val) {}
		Vector2f(float _x, float _y) : x(_x), y(_y) {}
		Vector2f(const Vector2f& other) : x(other.x), y(other.y) {}

		Vector2f operator + (const Vector2f& other) const { return Vector2f(x + other.x, y + other.y); }
		Vector2f operator - (const Vector2f& other) const { return Vector2f(x - other.x, y - other.y); }
		Vector2f& operator += (const Vector2f& other) { x += other.x; y += other.y; return *this; }
		Vector2f& operator -= (const Vector2f& other) { x -= other.x; y -= other.y; return *this; }

		Vector2f operator * (const Vector2f& other) const { return Vector2f(x * other.x, y * other.y); }
		Vector2f operator / (const Vector2f& other) const { return Vector2f(x / other.x, y / other.y); }
		Vector2f& operator *= (const Vector2f& other) { x *= other.x; y *= other.y; return *this; }
		Vector2f& operator /= (const Vector2f& other) { x /= other.x; y /= other.y; return *this; }

		Vector2f operator * (float val) const { return Vector2f(x * val, y * val); }
		Vector2f operator / (float val) const { return Vector2f(x / val, y / val); }
		Vector2f& operator *= (float val) { x *= val; y *= val; return *this; }
		Vector2f& operator /= (float val) { x /= val; y /= val; return *this; }

		static const Vector2f ZERO;
		static const Vector2f ONE;
	};

	//////////////////////////////////////////////////////////////////////////
	class Vector2i
	{
	public:
		union
		{
			int m[2];
			struct
			{
				int x;
				int y;
			};
		};

		Vector2i() {}
		explicit Vector2i(int val) : x(val), y(val) {}
		Vector2i(int _x, int _y) : x(_x), y(_y) {}
		Vector2i(const Vector2i& other) : x(other.x), y(other.y) {}

		Vector2i operator + (const Vector2i& other) const { return Vector2i(x + other.x, y + other.y); }
		Vector2i operator - (const Vector2i& other) const { return Vector2i(x - other.x, y - other.y); }
		Vector2i& operator += (const Vector2i& other) { x += other.x; y += other.y; return *this; }
		Vector2i& operator -= (const Vector2i& other) { x -= other.x; y -= other.y; return *this; }

		Vector2i operator * (int val) const { return Vector2i(x * val, y * val); }
		Vector2i& operator *= (int val) { x *= val; y *= val; return *this; }

		static const Vector2i ZERO;
		static const Vector2i ONE;
	};
}