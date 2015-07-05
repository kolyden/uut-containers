#include "uutGeometry.h"
#include "uutRender.h"
#include "uutVertexBuffer.h"
#include "uutIndexBuffer.h"
#include "uutVertexLayout.h"

namespace uut
{
	Geometry::Geometry(Render* render, int vertexCount /* = 2048 */, int indexCount /* = 4096 */)
		: _render(render)
		, _vertexCount(vertexCount)
		, _indexCount(indexCount)
		, _type(PRIMITIVE_TRIANGLELIST)
	{
	}

	void Geometry::SetPrimitive(EPrimitiveType type)
	{
		_type = type;
	}

	EPrimitiveType Geometry::GetPrimitive() const
	{
		return _type;
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

	void Geometry::SetUV(const List<Vector2f>& uvs)
	{
		_uvs = uvs;
	}

	const List<Vector2f>& Geometry::GetUV() const
	{
		return _uvs;
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
		{
			_vbuffer = _render->CreateVertexBuffer(USAGE_DYNAMIC,
				sizeof(Vertex)*_vertexCount);
		}

		if (!_ibuffer)
		{
			_ibuffer = _render->CreateIndexBuffer(USAGE_DYNAMIC,
				sizeof(uint16_t)*_indexCount, INDEX_16);
		}

		if (!_layout)
			_layout = _render->CreateVertexLayout(Vertex::DECLARE);

		if (!_vbuffer || !_ibuffer || !_layout)
			return false;

		auto vert = (Vertex*)_vbuffer->Lock();
		for (int i = 0; i < _vertices.Count(); i++)
		{
			vert[i].pos = _vertices[i];
			vert[i].color = _colors[i];
			vert[i].tex = _uvs[i];
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
		switch (_type)
		{
		case PRIMITIVE_POINTLIST: primitiveCount = _indexes.Count(); break;
		case PRIMITIVE_LINELIST: primitiveCount = _indexes.Count() / 2; break;
		case PRIMITIVE_TRIANGLELIST:
			primitiveCount = _indexes.Count() / 3;
			break;
		}
		_render->SetVertexLayout(_layout);
		_render->SetVertexBuffer(0, _vbuffer, 0, sizeof(Vertex));
		_render->SetIndexBuffer(_ibuffer);
		_render->DrawIndexedPrimitive(_type, 0, 0,
			_vertices.Count(), 0, primitiveCount);
	}
}