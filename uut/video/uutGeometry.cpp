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
		Color4b color;
	};

	static const int BUFFER_SIZE = sizeof(VERTEX)* 1000;

	Geometry::Geometry(Render* render)
		: _render(render)
	{
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
			_vbuffer = _render->CreateVertexBuffer(BUFFER_SIZE, VERTEX::FORMAT);

		if (!_ibuffer)
			_ibuffer = _render->CreateIndexBuffer(BUFFER_SIZE, INDEX_16);

		if (!_vbuffer || !_ibuffer)
			return false;

		VERTEX* vert = (VERTEX*)_vbuffer->Lock();
		for (int i = 0; i < _vertices.Count(); i++)
		{
			vert[i].pos = _vertices[i];
			vert[i].color = _colors[i];
		}
		_vbuffer->Unlock();

		uint16_t* indx = (uint16_t*)_ibuffer->Lock();
		memcpy(indx, _indexes.GetData(), sizeof(uint16_t)* _indexes.Count());
		_ibuffer->Unlock();

		return true;
	}

	void Geometry::Draw()
	{
		_render->SetVertexFormat(VERTEX::FORMAT);
		_render->SetVertexBuffer(_vbuffer, 0, sizeof(VERTEX));
		_render->SetIndexBuffer(_ibuffer);
		_render->DrawIndexedPrimitive( PRIMITIVE_TRIANGLELIST, 0, 0, _vertices.Count(), 0, _indexes.Count() / 3);
	}
}