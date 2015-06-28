#include "uutMatrix.h"
#include <d3dx9.h>

namespace uut
{
	Matrix4::Matrix4() {}

	Matrix4::Matrix4(const float* mat)
	{
		memcpy(m, mat, sizeof(float) * 16);
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
