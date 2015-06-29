#pragma once
#include "uutVector3.h"
#include "uutMatrix.h"
#include "uutQuaternion.h"

namespace uut
{
	class Camera
	{
	public:
		Camera();

		void SetPosition(const Vector3f& pos);
		const Vector3f& GetPosition() const;

		void SetRotation(const Quaternion& rotation);
		const Quaternion& GetRotation() const;

		void Move(const Vector3f& delta) { SetPosition(GetPosition() + delta); }

		const Matrix4& Generate();

	protected:
		Vector3f _position;
		Quaternion _rotation;
		
		Matrix4 _mat;
		bool _update;
	};
}