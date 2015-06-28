#pragma once
#include "uutRect.h"
#include "uutVector3.h"

namespace uut
{
	class Matrix4
	{
	public:
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
			float data[16];
		};

		Matrix4();
		Matrix4(const float* mat);

		static Matrix4 MakeIdentity();
		static Matrix4 MakeTranslate(const Vector3f& vec);
		static Matrix4 MakeRotateX(float angle);
		static Matrix4 MakeRotateY(float angle);
		static Matrix4 MakeRotateZ(float angle);
		static Matrix4 MakeScaling(const Vector3f& scale);

		static Matrix4 MakePerspective(float fovy, float aspect,
			float znear, float zfar);
		static Matrix4 MakeLookAt(const Vector3f& eye, const Vector3f& at, const Vector3f& up);
	};
}