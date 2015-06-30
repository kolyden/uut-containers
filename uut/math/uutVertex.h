#pragma once
#include "uutVector3.h"
#include "uutColor.h"

namespace uut
{
	struct Vertex
	{
		Vector3f pos;
		Color4b color;

		Vertex() {}
		Vertex(float x, float y, float z)
			: pos(x, y, z), color(Color4b::WHITE)
		{}

		Vertex(const Vector3f& _pos)
			: pos(_pos), color(Color4b::WHITE)
		{}
		Vertex(const Vector3f& _pos, const Color4b& _color)
			: pos(_pos), color(_color)
		{}

	};
}