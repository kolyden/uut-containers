#include "uutGeometry.h"
#include "uutVideo.h"
#include "uutShader.h"
#include "uutVideoBuffer.h"

namespace uut
{
	static const char* g_shader =
		"cbuffer cbPerObject \
		{ \
			float4x4 WVP; \
		}; \
		struct VS_OUTPUT \
		{ \
			float4 Pos : SV_POSITION; \
			float4 Color : COLOR; \
		}; \
		VS_OUTPUT VS(float4 inPos : POSITION, float4 inColor : COLOR) \
		{ \
			VS_OUTPUT output; \
			output.Pos = mul(inPos, WVP); \
			output.Color = inColor; \
			return output; \
		} \
		float4 PS(VS_OUTPUT input) : SV_TARGET \
		{ \
			return input.Color; \
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
			_vbuffer = _video->CreateBuffer(BufferType::Vertex, BufferUsage::Dynamic, 2048);

		if (!_ibuffer)
			_ibuffer = _video->CreateBuffer(BufferType::Index, BufferUsage::Dynamic, 2048);

		if (!_shader || !_vbuffer || !_ibuffer)
			return false;

		VERTEX* vert = (VERTEX*)_vbuffer->Map();
		for (int i = 0; i < _vertices.Count(); i++)
		{
			vert[i].pos = _vertices[i];
			vert[i].color = _colors[i];
		}
		_vbuffer->Unmap();

		_ibuffer->Update(_indexes.GetData(), sizeof(uint16_t)* _indexes.Count());

		return true;
	}

	void Geometry::Draw()
	{
		_video->SetShader(_shader);
		_video->SetVertexBuffer(_vbuffer, sizeof(VERTEX), 0);
		_video->SetIndexBuffer(_ibuffer, IndexType::Uint16, 0);
		_video->SetTopology(VertexTopology::TriangleList);
		_video->DrawIndexed(_indexes.Count(), 0, 0);
	}
}