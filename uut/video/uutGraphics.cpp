#include "uutGraphics.h"
#include "uutRender.h"
#include "uutGeometry.h"

namespace uut
{
	static const int MAX_VERTS = 2048;
	static const int MAX_INDEX = 4096;

	Graphics::Graphics(Render* render)
		: _render(render)
		, _primitive(PRIMITIVE_TRIANGLELIST)
	{
		_geometry = new Geometry(_render, MAX_VERTS, MAX_INDEX);
	}

	void Graphics::DrawLine(const Vertex& start, const Vertex& end)
	{
		TestBatch(PRIMITIVE_LINELIST, 2, 2);
		const int count = _verts.Count();
		_verts << start << end;
		_indexes << count << count + 1;
	}

	void Graphics::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
	{
		TestBatch(PRIMITIVE_TRIANGLELIST, 3, 3);
		const int count = _verts.Count();
		_verts << v0 << v1 << v2;
		_indexes << count << count + 1 << count + 2;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		TestBatch(PRIMITIVE_TRIANGLELIST, 4, 6);
		const int count = _verts.Count();
		_verts << v0 << v1 << v2 << v3;
		_indexes << count + 0 << count + 1 << count + 3;
		_indexes << count + 3 << count + 1 << count + 2;
	}

	void Graphics::Flush()
	{
		if (_verts.IsEmpty())
			return;

		static List<Vector3f> verts;
		static List<Color4b> colors;

		verts.SetSize(_verts.Count());
		colors.SetSize(_verts.Count());
		for (int i = 0; i < _verts.Count(); i++)
		{
			verts[i] = _verts[i].pos;
			colors[i] = _verts[i].color;
		}

		_geometry->SetPrimitive(_primitive);
		_geometry->SetVertices(verts);
		_geometry->SetColors(colors);
		_geometry->SetIndexes(_indexes);
		_geometry->Generate();
		_geometry->Draw();

		_verts.Clear();
		_indexes.Clear();
	}

	void Graphics::TestBatch(EPrimitiveType type, int vertsCount, int indexCount)
	{
		if (!_verts.IsEmpty() && (_primitive != type || _verts.Count() + vertsCount >= MAX_VERTS || _indexes.Count() + indexCount >= MAX_INDEX))
		{
			Flush();
		}

		_primitive = type;
	}
}