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
		FromAngleAxis(axis, angle);
	}

	Quaternion::Quaternion(float _x, float _y, float _z)
	{
		FromEulerAngles(Vector3f(_x, _y, _z));
	}

	Quaternion::Quaternion(const Vector3f& angles)
	{
		FromEulerAngles(angles);
	}

	void Quaternion::FromAngleAxis(const Vector3f& axis, float angle)
	{
		Vector3f normAxis = axis.Normalized();
		angle *= Math::M_DEGTORAD_2;
		const float sinAngle = sinf(angle);
		const float cosAngle = cosf(angle);

		w = cosAngle;
		x = normAxis.x * sinAngle;
		y = normAxis.y * sinAngle;
		z = normAxis.z * sinAngle;
	}

	void Quaternion::FromEulerAngles(float _x, float _y, float _z)
	{
		FromEulerAngles(Vector3f(_x, _y, _z));
	}

	void Quaternion::FromEulerAngles(const Vector3f& angles)
	{
		const float nx = angles.x * Math::M_DEGTORAD_2;
		const float ny = angles.y * Math::M_DEGTORAD_2;
		const float nz = angles.z * Math::M_DEGTORAD_2;
		float sinX = sinf(nx);
		float cosX = cosf(nx);
		float sinY = sinf(ny);
		float cosY = cosf(ny);
		float sinZ = sinf(nz);
		float cosZ = cosf(nz);

		w = cosY * cosX * cosZ + sinY * sinX * sinZ;
		x = cosY * sinX * cosZ + sinY * cosX * sinZ;
		y = sinY * cosX * cosZ - cosY * sinX * sinZ;
		z = cosY * cosX * sinZ - sinY * sinX * cosZ;
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