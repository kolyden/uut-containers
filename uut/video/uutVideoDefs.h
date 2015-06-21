#pragma once
#include "core/uutDefs.h"
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

namespace uut
{
	using namespace DirectX;

	enum class BufferType
	{
		Vertex,
		Pixel,
	};

	enum class BufferUsage
	{
		Default,
		Dynamic,
	};

	enum class VertexTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,
	};

	enum class VertexUsage
	{
		Position,
		TexCoords,
		Color,
	};

	enum class VertexType
	{
		SByte,
		UByte,
		SShort,
		UShort,
		Float,
	};

	struct VertexDeclare
	{
		uint8_t _index;
		VertexUsage _usage;
		VertexType _type;
		uint8_t _count;
		uint16_t _offset;
	};
}