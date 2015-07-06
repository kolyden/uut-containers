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

	enum VertexTopology
	{
		PRIMITIVE_POINTLIST,
		PRIMITIVE_LINELIST,
		PRIMITIVE_LINESTRIP,
		PRIMITIVE_TRIANGLELIST,
		PRIMITIVE_TRIANGLESTRIP,
	};

	enum BufferUsage
	{
		USAGE_DEFAULT,
		USAGE_DYNAMIC,
	};

	enum DeclareType
	{
		VALUE_BYTE,
		VALUE_UBYTE,
		VALUE_SHORT,
		VALUE_USHORT,
		VALUE_FLOAT,
		VALUE_FIXED,
		VALUE_DWORD,
	};

	enum DeclareUsage
	{
		DECLARE_POSITION,
		DECLARE_COLOR,
		DECLARE_TEXCOORDS,
	};

	struct VertexDeclare
	{
		DeclareUsage usage;
		DeclareType type;
		uint8_t count;
		uint16_t offset;
		uint8_t stream;
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