#include "uutQuaternion.h"
#include <d3dx9.h>

namespace uut
{
	const Quaternion Quaternion::IDENTITY(0, 0, 0, 1);

	Quaternion::Quaternion() {}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{
	}

	Quaternion::Quaternion(const Vector3f& axis, float angle)
	{
		angle /= 2.0f;

		const float sinAngle = sin(angle);
		x = (sinAngle * axis.x);
		y = (sinAngle * axis.y);
		z = (sinAngle * axis.z);
		w = cos(angle);
	}

	Quaternion::Quaternion(float yaw, float pitch, float roll)
	{
		D3DXQuaternionRotationYawPitchRoll(
			(D3DXQUATERNION*)this, yaw, pitch, roll);
	}

	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
	}

	Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
	{
		const float theta = acosf(Dot(a, b));
		const float sinTheta = sinf(theta);
		const float t1 = sinf((1.0f - t) * theta) / sinTheta;
		const float t2 = sinf(t * theta) / sinTheta;

		return Quaternion(
			a.x * t1 + b.x * t2,
			a.y * t1 + b.y * t2,
			a.z * t1 + b.z * t2,
			a.w * t1 + b.w * t2);
	}
}