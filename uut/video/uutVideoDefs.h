#pragma once
#include "core/uutDefs.h"
#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")

namespace uut
{
	enum class BufferType
	{
		Vertex,
		Index,
		Constant,
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
		Color,
		TexCoords,
	};

	enum class VertexType
	{
		SByte,
		UByte,
		SShort,
		UShort,
		Float,
	};

	enum class IndexType
	{
		Uint16,
		Uint32,
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