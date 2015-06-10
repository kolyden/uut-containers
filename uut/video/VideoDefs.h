#pragma once
#include "core/Defs.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

namespace uut
{
	enum class ShaderType
	{
		Vertex,
		Pixel,
	};

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