#pragma once
#include "containers/uutList.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "uutColor.h"
#include "uutVideoDefs.h"

namespace uut
{
	struct Vertex
	{
		static const List<VertexDeclare> DECLARE;

		Vector3f pos;
		Color4b color;
		Vector2f tex;

		Vertex() {}
		Vertex(float x, float y, float z)
			: pos(x, y, z), color(Color4b::WHITE), tex(Vector2f::ZERO)
		{}

		Vertex(const Vector3f& _pos)
			: pos(_pos), color(Color4b::WHITE), tex(Vector2f::ZERO)
		{}

		Vertex(const Vector3f& _pos, const Color4b& _color)
			: pos(_pos), color(_color), tex(Vector2f::ZERO)
		{}

		Vertex(const Vector3f& _pos, const Color4b& _color, const Vector2f& _tex)
			: pos(_pos), color(_color), tex(_tex)
		{}

	};
}