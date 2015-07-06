#pragma once
#include "containers/uutList.h"
#include "core/uutModule.h"
#include "uutVertex.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Render;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class VertexLayout;

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
		static const int MAX_VERTEX = 1024 * 2;
		static const int MAX_INDEX = 1024 * 4;

		WeakPtr<Render> _render;
		VertexTopology _topology;
		Vertex _verts[MAX_VERTEX];
		uint16_t _indexes[MAX_INDEX];
		uint16_t _vertsCount;
		uint16_t _indexesCount;
		uint16_t _primitiveCount;
		SharedPtr<Texture> _texture;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
		SharedPtr<VertexLayout> _layout;

		void TestBatch(VertexTopology type, int vertsCount, int indexCount, Texture* tex);
	};
}