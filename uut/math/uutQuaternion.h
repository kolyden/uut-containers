#pragma once
#include "uutVector3.h"

namespace uut
{
	class Quaternion
	{
	public:
		union
		{
			float m[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3f& axis, float angle);
		Quaternion(float x, float y, float z);
		Quaternion(const Vector3f& angles);

		void FromAngleAxis(const Vector3f& axis, float angle);
		void FromEulerAngles(float x, float y, float z);
		void FromEulerAngles(const Vector3f& angles);

		static float Dot(const Quaternion& a, const Quaternion& b);
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

		static const Quaternion IDENTITY;
	};
}