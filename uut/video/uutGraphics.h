#pragma once
#include "core/uutModule.h"
#include "math/uutVertex.h"
#include "containers/uutList.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Render;
	class Geometry;

	class Graphics : public Module
	{
		OBJECT(Graphics, Module)
	public:
		Graphics(Render* render);

		void DrawLine(const Vertex& start, const Vertex& end);
		void DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
		void DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3);

		void Flush();

	protected:
		WeakPtr<Render> _render;
		SharedPtr<Geometry> _geometry;
		EPrimitiveType _primitive;
		List<Vertex> _verts;
		List<uint16_t> _indexes;

		void TestBatch(EPrimitiveType type, int vertsCount, int indexCount);
	};
}