#pragma once
#include "core/uutDefs.h"
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

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

	enum EPrimitiveType
	{
		PRIMITIVE_POINTLIST,
		PRIMITIVE_LINELIST,
		PRIMITIVE_LINESTRIP,
		PRIMITIVE_TRIANGLELIST,
		PRIMITIVE_TRIANGLESTRIP,
	};

	enum VertexFormat
	{
		VERTEX_XYZ        = 1,
		VERTEX_XYZRHW     = 2,
		VERTEX_COLOR      = 4,
		VERTEX_TEXCOORDS0 = 8,
	};

	enum ETransformType
	{
		TRANSFORM_WORLD,
		TRANSFORM_VIEW,
		TRANSFORM_PROJECTION,
	};

	enum ERenderState
	{
		RENDERSTATE_LIGHTNING,
		RENDERSTATE_ZENABLE,
	};

	enum EIndexFormat
	{
		INDEX_16,
		INDEX_32,
	};
}