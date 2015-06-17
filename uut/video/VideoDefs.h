#pragma once
#include "core/Defs.h"
#include <d3d11.h>
#include <D3Dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")

namespace uut
{
	enum class VideoBufferType
	{
		Vertex,
		Index,
	};

	enum class VertexTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,
	};
}