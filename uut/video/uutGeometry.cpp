#include "uutGeometry.h"
#include "uutRender.h"
#include "uutVertexBuffer.h"
#include "uutIndexBuffer.h"

namespace uut
{
	struct VERTEX
	{
		static const int FORMAT = VERTEX_XYZ | VERTEX_COLOR;
		Vector3f pos;
		D3DCOLOR color;
	};

	Geometry::Geometry(Render* render, int vertexCount /* = 2048 */, int indexCount /* = 4096 */)
		: _render(render)
		, _vertexCount(vertexCount)
		, _indexCount(indexCount)
		, _primitive(PRIMITIVE_TRIANGLELIST)
	{
	}

	void Geometry::SetPrimitive(EPrimitiveType type)
	{
		_primitive = type;
	}

	EPrimitiveType Geometry::GetPrimitive() const
	{
		return _primitive;
	}

	void Geometry::SetVertices(const List<Vector3f>& vertices)
	{
		_vertices = vertices;
	}

	const List<Vector3f>& Geometry::GetVertices() const
	{
		return _vertices;
	}

	void Geometry::SetColors(const List<Color4b>& colors)
	{
		_colors = colors;
	}

	const List<Color4b>& Geometry::GetColors() const
	{
		return _colors;
	}

	void Geometry::SetIndexes(const List<uint16_t>& indexes)
	{
		_indexes = indexes;
	}

	const List<uint16_t>& Geometry::GetIndexes() const
	{
		return _indexes;
	}

	bool Geometry::Generate()
	{
		if (!_vbuffer)
			_vbuffer = _render->CreateVertexBuffer(sizeof(VERTEX)*_vertexCount, VERTEX::FORMAT);

		if (!_ibuffer)
			_ibuffer = _render->CreateIndexBuffer(sizeof(uint16_t)*_indexCount, INDEX_16);

		if (!_vbuffer || !_ibuffer)
			return false;

		VERTEX* vert = (VERTEX*)_vbuffer->Lock();
		for (int i = 0; i < _vertices.Count(); i++)
		{
			vert[i].pos = _vertices[i];
			vert[i].color = D3DCOLOR_ARGB(_colors[i].a, _colors[i].r, _colors[i].g, _colors[i].b);
		}
		_vbuffer->Unlock();

		uint16_t* indx = (uint16_t*)_ibuffer->Lock();
		memcpy(indx, _indexes.GetData(), sizeof(uint16_t)* _indexes.Count());
		_ibuffer->Unlock();

		return true;
	}

	void Geometry::Clear()
	{
		_vertices.Clear();
		_colors.Clear();
		_indexes.Clear();
	}

	void Geometry::Draw()
	{
		int primitiveCount = 0;
		switch (_primitive)
		{
		case PRIMITIVE_POINTLIST: primitiveCount = _indexes.Count(); break;
		case PRIMITIVE_LINELIST: primitiveCount = _indexes.Count() / 2; break;
		case PRIMITIVE_TRIANGLELIST:
			primitiveCount = _indexes.Count() / 3;
			break;
		}
		_render->SetVertexFormat(VERTEX::FORMAT);
		_render->SetVertexBuffer(_vbuffer, 0, sizeof(VERTEX));
		_render->SetIndexBuffer(_ibuffer);
		_render->DrawIndexedPrimitive(_primitive, 0, 0,
			_vertices.Count(), 0, primitiveCount);
	}
}