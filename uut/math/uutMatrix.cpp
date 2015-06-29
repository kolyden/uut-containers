#include "uutMatrix.h"
#include <d3dx9.h>

namespace uut
{
	const Matrix4 Matrix4::EMPTY(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	const Matrix4 Matrix4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4::Matrix4() {}

	Matrix4::Matrix4(const float* mat)
	{
		memcpy(m, mat, sizeof(float) * 16);
	}

	Matrix4::Matrix4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
		: _11(m11), _12(m12), _13(m13), _14(m14)
		, _21(m21), _22(m22), _23(m23), _24(m24)
		, _31(m31), _32(m32), _33(m33), _34(m34)
		, _41(m41), _42(m42), _43(m43), _44(m44)
	{

	}

	Matrix4& Matrix4::operator+=(const Matrix4& mat)
	{
		_11 += mat._11;
		_12 += mat._12;
		_13 += mat._13;
		_14 += mat._14;

		_21 += mat._21;
		_22 += mat._22;
		_23 += mat._23;
		_24 += mat._24;

		_31 += mat._31;
		_32 += mat._32;
		_33 += mat._33;
		_34 += mat._34;

		_41 += mat._41;
		_42 += mat._42;
		_43 += mat._43;
		_44 += mat._44;

		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& mat)
	{
		_11 -= mat._11;
		_12 -= mat._12;
		_13 -= mat._13;
		_14 -= mat._14;

		_21 -= mat._21;
		_22 -= mat._22;
		_23 -= mat._23;
		_24 -= mat._24;

		_31 -= mat._31;
		_32 -= mat._32;
		_33 -= mat._33;
		_34 -= mat._34;

		_41 -= mat._41;
		_42 -= mat._42;
		_43 -= mat._43;
		_44 -= mat._44;

		return *this;
	}


	Matrix4& Matrix4::operator*=(float v)
	{
		_11 *= v;
		_12 *= v;
		_13 *= v;
		_14 *= v;

		_21 *= v;
		_22 *= v;
		_23 *= v;
		_24 *= v;

		_31 *= v;
		_32 *= v;
		_33 *= v;
		_34 *= v;

		_41 *= v;
		_42 *= v;
		_43 *= v;
		_44 *= v;

		return *this;
	}

	Matrix4& Matrix4::operator/=(float v)
	{
		_11 /= v;
		_12 /= v;
		_13 /= v;
		_14 /= v;

		_21 /= v;
		_22 /= v;
		_23 /= v;
		_24 /= v;

		_31 /= v;
		_32 /= v;
		_33 /= v;
		_34 /= v;

		_41 /= v;
		_42 /= v;
		_43 /= v;
		_44 /= v;

		return *this;
	}

	Matrix4 Matrix4::operator-() const
	{
		Matrix4 pOut;

		pOut._11 = -_11;
		pOut._12 = -_12;
		pOut._13 = -_13;
		pOut._14 = -_14;

		pOut._21 = -_21;
		pOut._22 = -_22;
		pOut._23 = -_23;
		pOut._24 = -_24;

		pOut._31 = -_31;
		pOut._32 = -_32;
		pOut._33 = -_33;
		pOut._34 = -_34;

		pOut._41 = -_41;
		pOut._42 = -_42;
		pOut._43 = -_43;
		pOut._44 = -_44;

		return pOut;
	}

	Matrix4 Matrix4::operator+ (const Matrix4& pM) const
	{
		Matrix4 pOut;

		pOut._11 = _11 + pM._11;
		pOut._12 = _12 + pM._12;
		pOut._13 = _13 + pM._13;
		pOut._14 = _14 + pM._14;

		pOut._21 = _21 + pM._21;
		pOut._22 = _22 + pM._22;
		pOut._23 = _23 + pM._23;
		pOut._24 = _24 + pM._24;

		pOut._31 = _31 + pM._31;
		pOut._32 = _32 + pM._32;
		pOut._33 = _33 + pM._33;
		pOut._34 = _34 + pM._34;

		pOut._41 = _41 + pM._41;
		pOut._42 = _42 + pM._42;
		pOut._43 = _43 + pM._43;
		pOut._44 = _44 + pM._44;

		return pOut;
	}

	Matrix4 Matrix4::operator- (const Matrix4& pM) const
	{
		Matrix4 pOut;

		pOut._11 = _11 - pM._11;
		pOut._12 = _12 - pM._12;
		pOut._13 = _13 - pM._13;
		pOut._14 = _14 - pM._14;

		pOut._21 = _21 - pM._21;
		pOut._22 = _22 - pM._22;
		pOut._23 = _23 - pM._23;
		pOut._24 = _24 - pM._24;

		pOut._31 = _31 - pM._31;
		pOut._32 = _32 - pM._32;
		pOut._33 = _33 - pM._33;
		pOut._34 = _34 - pM._34;

		pOut._41 = _41 - pM._41;
		pOut._42 = _42 - pM._42;
		pOut._43 = _43 - pM._43;
		pOut._44 = _44 - pM._44;

		return pOut;
	}

	Matrix4 Matrix4::operator*(float v) const
	{
		Matrix4 pOut;

		pOut._11 = _11 * v;
		pOut._12 = _12 * v;
		pOut._13 = _13 * v;
		pOut._14 = _14 * v;

		pOut._21 = _21 * v;
		pOut._22 = _22 * v;
		pOut._23 = _23 * v;
		pOut._24 = _24 * v;

		pOut._31 = _31 * v;
		pOut._32 = _32 * v;
		pOut._33 = _33 * v;
		pOut._34 = _34 * v;

		pOut._41 = _41 * v;
		pOut._42 = _42 * v;
		pOut._43 = _43 * v;
		pOut._44 = _44 * v;

		return pOut;
	}

	Matrix4 Matrix4::operator/(float v) const
	{
		Matrix4 pOut;

		pOut._11 = _11 / v;
		pOut._12 = _12 / v;
		pOut._13 = _13 / v;
		pOut._14 = _14 / v;

		pOut._21 = _21 / v;
		pOut._22 = _22 / v;
		pOut._23 = _23 / v;
		pOut._24 = _24 / v;

		pOut._31 = _31 / v;
		pOut._32 = _32 / v;
		pOut._33 = _33 / v;
		pOut._34 = _34 / v;

		pOut._41 = _41 / v;
		pOut._42 = _42 / v;
		pOut._43 = _43 / v;
		pOut._44 = _44 / v;

		return pOut;
	}

	Vector3f Matrix4::Transform(const Vector3f& pV) const
	{
		Vector3f pOut;
		pOut.x = pV.x * _11 + pV.y * _21 + pV.z * _31;
		pOut.y = pV.x * _12 + pV.y * _22 + pV.z * _32;
		pOut.z = pV.x * _13 + pV.y * _23 + pV.z * _33;
		return pOut;
	}

	Matrix4 Matrix4::MakeIdentity()
	{
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		return Matrix4(&mat._11);
	}

	Matrix4 Matrix4::MakeTranslate(const Vector3f& vec)
	{
		D3DXMATRIX mat;
		D3DXMatrixTranslation(&mat, vec.x, vec.y, vec.z);
		return Matrix4(&mat._11);
	}

	Matrix4 Matrix4::MakeRotateX(float angle)
	{
		D3DXMATRIX mat;
		D3DXMatrixRotationX(&mat, angle);
		return Matrix4(&mat._11);
	}

	Matrix4 Matrix4::MakeRotateY(float angle)
	{
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, angle);
		return Matrix4(&mat._11);
	}

	Matrix4 Matrix4::MakeRotateZ(float angle)
	{
		D3DXMATRIX mat;
		D3DXMatrixRotationZ(&mat, angle);
		return Matrix4(&mat._11);
	}

	uut::Matrix4 Matrix4::MakeScaling(const Vector3f& scale)
	{
		D3DXMATRIX mat;
		D3DXMatrixScaling(&mat, scale.x, scale.y, scale.z);
		return Matrix4(&mat._11);
	}

	uut::Matrix4 Matrix4::MakeQuaternion(const Quaternion& quaternion)
	{
		D3DXMATRIX mat;
		D3DXMatrixRotationQuaternion(&mat, (D3DXQUATERNION*)&quaternion);
		return Matrix4(mat);
	}

	Matrix4 Matrix4::MakePerspective(float fovy, float aspect, float znear, float zfar)
	{
		D3DXMATRIX mat;
		D3DXMatrixPerspectiveFovLH(&mat, fovy, aspect, znear, zfar);
		return Matrix4(&mat._11);
	}

	uut::Matrix4 Matrix4::MakeLookAt(const Vector3f& eye, const Vector3f& at, const Vector3f& up)
	{
		D3DXMATRIX mat;
		D3DXVECTOR3 v0(eye.x, eye.y, eye.z);
		D3DXVECTOR3 v1(at.x, at.y, at.z);
		D3DXVECTOR3 v2(up.x, up.y, up.z);
		D3DXMatrixLookAtLH(&mat, &v0, &v1, &v2);
		return Matrix4(&mat._11);
	}
}
