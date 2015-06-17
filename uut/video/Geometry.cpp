#include "Geometry.h"
#include "Video.h"
#include "VideoBuffer.h"
#include "Shader.h"
#include "BufferLayout.h"
#include "Color.h"

namespace uut
{
	struct VERTEX
	{
		FLOAT x, y, z;      // position
		Color color;    // color
	};

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	static const int BUFFER_SIZE = sizeof(VERTEX)* 1000;

	Geometry::Geometry(Video* video)
		: VideoObject(video)
	{
	}

	void Geometry::SetVertices(const List<Vector3>& vertices)
	{
		_vertices = vertices;
	}

	const List<Vector3>& Geometry::GetVertices() const
	{
		return _vertices;
	}

	void Geometry::SetColors(const List<Color>& colors)
	{
		_colors = colors;
	}

	const List<Color>& Geometry::GetColors() const
	{
		return _colors;
	}

	bool Geometry::Generate()
	{
		return true;
	}
}