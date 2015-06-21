#include "uutGeometry.h"
#include "uutVideo.h"
#include "uutVertexBuffer.h"
#include "uutShader.h"

namespace uut
{
	static const char* g_shader =
		"struct VOut \
		{ \
			float4 position : SV_POSITION; \
			float4 color : COLOR; \
		}; \
		VOut VShader(float4 position : POSITION, float4 color : COLOR) \
		{ \
			VOut output; \
			output.position = position; \
			output.color = color; \
			return output; \
		} \
		float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET \
		{ \
			return color; \
		}";

	struct VERTEX
	{
		Vector3 pos;
		Color color;
	};

	uut::VertexDeclare g_decl[] =
	{
		{ 0, uut::VertexUsage::Position, uut::VertexType::Float, 3, 0 },
		{ 0, uut::VertexUsage::Color, uut::VertexType::Float, 4, sizeof(float)* 3 },
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
		if (!_shader)
			_shader = _video->CreateShaderFromMemory(g_decl, 2, g_shader);

		if (!_vbuffer)
			_vbuffer = _video->CreateVertexBuffer(BufferUsage::Dynamic, 2048);

		if (!_shader || !_vbuffer)// || !_ibuffer)
			return false;

		VERTEX* vert = (VERTEX*)_vbuffer->Map();
		for (int i = 0; i < _vertices.Count(); i++)
		{
			vert[i].pos = _vertices[i];
			vert[i].color = _colors[i];
		}
		_vbuffer->Unmap();

		return true;
	}

	void Geometry::Draw()
	{
		_video->SetShader(_shader);
		_video->SetBuffer(_vbuffer, sizeof(VERTEX), 0);
		_video->SetTopology(VertexTopology::TriangleList);
		_video->Draw(_vertices.Count(), 0);
	}
}