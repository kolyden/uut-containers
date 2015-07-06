#include "uutGraphics.h"
#include "uutRender.h"
#include "uutTexture.h"
#include "uutVertexBuffer.h"
#include "uutIndexBuffer.h"
#include "uutVertexLayout.h"

namespace uut
{
	Graphics::Graphics(Render* render)
		: _render(render)
		, _topology(PRIMITIVE_TRIANGLELIST)
		, _vertsCount(0)
		, _indexesCount(0)
		, _primitiveCount(0)
	{
		_vbuffer = _render->CreateVertexBuffer(USAGE_DYNAMIC, sizeof(Vertex)* MAX_VERTEX);
		_ibuffer = _render->CreateIndexBuffer(USAGE_DYNAMIC, sizeof(uint16_t)* MAX_INDEX, INDEX_16);
		_layout = _render->CreateVertexLayout(Vertex::DECLARE);
	}

	void Graphics::DrawLine(const Vertex& start, const Vertex& end)
	{
		TestBatch(PRIMITIVE_LINELIST, 2, 2, nullptr);

		_indexes[_indexesCount++] = _vertsCount + 0;
		_indexes[_indexesCount++] = _vertsCount + 1;
		_verts[_vertsCount++] = start;
		_verts[_vertsCount++] = end;
		_primitiveCount++;
	}

	void Graphics::DrawTriangle(const Vertex& v0, const Vertex& v1,
		const Vertex& v2, Texture* tex /* = nullptr */)
	{
		TestBatch(PRIMITIVE_TRIANGLELIST, 3, 3, tex);

		_indexes[_indexesCount++] = _vertsCount + 0;
		_indexes[_indexesCount++] = _vertsCount + 1;
		_indexes[_indexesCount++] = _vertsCount + 2;
		_verts[_vertsCount++] = v0;
		_verts[_vertsCount++] = v1;
		_verts[_vertsCount++] = v2;
		_primitiveCount++;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1,
		const Vertex& v2, const Vertex& v3, Texture* tex /* = nullptr */)
	{
		TestBatch(PRIMITIVE_TRIANGLELIST, 4, 6, tex);

		_indexes[_indexesCount++] = _vertsCount + 0;
		_indexes[_indexesCount++] = _vertsCount + 1;
		_indexes[_indexesCount++] = _vertsCount + 3;
		_indexes[_indexesCount++] = _vertsCount + 3;
		_indexes[_indexesCount++] = _vertsCount + 1;
		_indexes[_indexesCount++] = _vertsCount + 2;

		_verts[_vertsCount++] = v0;
		_verts[_vertsCount++] = v1;
		_verts[_vertsCount++] = v2;
		_verts[_vertsCount++] = v3;
		_primitiveCount += 2;
	}

	void Graphics::Flush()
	{
		if (_vertsCount == 0)
			return;

		_vbuffer->Update(_verts, 0, _vertsCount * sizeof(Vertex));
		_ibuffer->Update(_indexes, 0, _indexesCount * sizeof(uint16_t));

		_render->SetTexture(0, _texture);
		_render->SetVertexBuffer(0, _vbuffer, 0, sizeof(Vertex));
		_render->SetIndexBuffer(_ibuffer);
		_render->SetVertexLayout(_layout);

		_render->DrawIndexedPrimitive(_topology, 0, 0, _vertsCount, 0, _primitiveCount);

		_vertsCount = 0;
		_indexesCount = 0;
		_primitiveCount = 0;
		_texture = nullptr;
	}

	void Graphics::TestBatch(VertexTopology type, int vertsCount, int indexCount, Texture* tex)
	{
		if (_topology != type ||
			_vertsCount + vertsCount >= MAX_VERTEX ||
			_indexesCount + indexCount >= MAX_INDEX ||
			_texture != tex)
		{
			Flush();
		}

		_topology = type;
		_texture = tex;
	}
}