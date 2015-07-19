#include "uutCamera.h"

namespace uut
{
	Camera::Camera()
		: _position(Vector3f::ZERO)
		, _rotation(Quaternion::IDENTITY)
		, _update(true)
	{
	}

	void Camera::SetPosition(const Vector3f& pos)
	{
		_position = pos;
		_update = true;
	}

	const Vector3f& Camera::GetPosition() const
	{
		return _position;
	}

	void Camera::SetRotation(const Quaternion& rotation)
	{
		_rotation = rotation;
		_update = true;
	}

	const Quaternion& Camera::GetRotation() const
	{
		return _rotation;
	}

	const Matrix4& Camera::Generate()
	{
		if (_update)
		{
			_update = false;
			auto mat = Matrix4::MakeQuaternion(_rotation);
			Vector3f at = _position + mat.Transform(Vector3f::AXIS_Z);
			_mat = Matrix4::MakeLookAt(_position, at, Vector3f::AXIS_Y);
		}

		return _mat;
	}
}