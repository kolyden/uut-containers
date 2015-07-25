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

	enum class TransformType
	{
		World,
		View,
		Projection,
	};

	enum class RenderState
	{
		Lightning,
		ZEnable,
		AlphaBlend,
		AlphaTest,
		ScissorTest,
	};

	enum RenderCull
	{
		CULL_NONE,
		CULL_CW,
		CULL_CCW,
	};

	enum IndexFormat
	{
		INDEX_16,
		INDEX_32,
	};

	enum ImageFormat
	{
		FORMAT_A8,
		FORMAT_A8R8G8B8,
	};

	enum BlendOperation
	{
		BLENDOP_ADD,
		BLENDOP_SUB,
		BLENDOP_REVSUB,
		BLENDOP_MIN,
		BLENDOP_MAX,
	};

	enum class BlendType
	{
		Source,
		Dest,
	};

	enum BlendMode
	{
		BLEND_ZERO,
		BLEND_ONE,
		BLEND_SRCCOLOR,
		BLEND_INVSRCCOLOR,
		BLEND_SRCALPHA,
		BLEND_INVSRCALPHA,
		BLEND_DESTALPHA,
		BLEND_INVDESTALPHA,
		BLEND_DESTCOLOR,
		BLEND_INVDESTCOLOR,
		BLEND_SRCALPHASAT,
		BLEND_BOTHSRCALPHA,
		BLEND_BOTHINVSRCALPHA,
	};

	enum TextureOperation
	{
		TSS_COLOROP,
		TSS_ALPHAOP,
		TSS_BUMPENVMAT00,
		TSS_BUMPENVMAT01,
		TSS_BUMPENVMAT10,
		TSS_BUMPENVMAT11,
		TSS_TEXCOORDINDEX,
		TSS_BUMPENVLSCALE,
		TSS_BUMPENVLOFFSET,
		TSS_TEXTURETRANSFORMFLAGS,
		TSS_CONSTANT,
	};

	enum TextureOperationValue
	{
		TEXOP_DISABLE,
		TEXOP_SELECTARG1,
		TEXOP_SELECTARG2,
		TEXOP_MODULATE,
		TEXOP_MODULATE2X,
		TEXOP_MODULATE4X,
		TEXOP_ADD,
		TEXOP_ADDSIGNED,
		TEXOP_ADDSIGNED2X,
		TEXOP_SUBTRACT,
		TEXOP_ADDSMOOTH,
		TEXOP_BLENDDIFFUSEALPHA,
		TEXOP_BLENDTEXTUREALPHA,
		TEXOP_BLENDFACTORALPHA,
		TEXOP_BLENDTEXTUREALPHAPM,
		TEXOP_BLENDCURRENTALPHA,
		TEXOP_PREMODULATE,
		TEXOP_MODULATEALPHA_ADDCOLOR,
		TEXOP_MODULATECOLOR_ADDALPHA,
		TEXOP_MODULATEINVALPHA_ADDCOLOR,
		TEXOP_MODULATEINVCOLOR_ADDALPHA,
		TEXOP_BUMPENVMAP,
		TEXOP_BUMPENVMAPLUMINANCE,
		TEXOP_DOTPRODUCT3,
		TEXOP_MULTIPLYADD,
		TEXOP_LERP,
	};

	enum TextureArgument
	{
		TSS_COLORARG0,
		TSS_COLORARG1,
		TSS_COLORARG2,
		TSS_ALPHAARG1,
		TSS_ALPHAARG0,
		TSS_ALPHAARG2,
		TSS_RESULTARG,
	};

	enum TextureArgumentValue
	{
		TEXARG_DIFFUSE,
		TEXARG_CURRENT,
		TEXARG_TEXTURE,
		TEXARG_TFACTOR,
		TEXARG_SPECULAR,
		TEXARG_TEMP,
		TEXARG_CONSTANT,
		TEXARG_COMPLEMENT,
		TEXARG_ALPHAREPLICATE,
	};

	enum TextureFilterTarget
	{
		TEXFILTERTARGET_MAG,
		TEXFILTERTARGET_MIN,
		TEXFILTERTARGET_MIP,
	};

	enum TextureFilterType
	{
		TEXFILTER_NONE,
		TEXFILTER_POINT,
		TEXFILTER_LINEAR,
		TEXFILTER_ANISOTROPIC,
		TEXFILTER_PYRAMIDALQUAD,
		TEXFILTER_GAUSSIANQUAD,
	};
}