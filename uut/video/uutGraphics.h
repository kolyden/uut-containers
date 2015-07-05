#pragma once
#include "containers/uutList.h"
#include "core/uutModule.h"
#include "uutVertex.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Render;
	class Geometry;
	class Texture;

	class Graphics : public Module
	{
		OBJECT(Graphics, Module)
	public:
		Graphics(Render* render);

		void DrawLine(const Vertex& start, const Vertex& end);
		void DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Texture* tex = nullptr);
		void DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, Texture* tex = nullptr);

		void Flush();

	protected:
		WeakPtr<Render> _render;
		SharedPtr<Geometry> _geometry;
		EPrimitiveType _primitive;
		List<Vertex> _verts;
		List<uint16_t> _indexes;
		SharedPtr<Texture> _texture;

		void TestBatch(EPrimitiveType type, int vertsCount, int indexCount, Texture* tex);
	};
}