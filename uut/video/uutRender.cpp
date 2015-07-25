#include "uutRender.h"
#include "application/uutWindow.h"
#include "uutVertexBuffer.h"
#include "uutIndexBuffer.h"
#include "uutTexture.h"
#include "uutVertexLayout.h"

namespace uut
{
	Render::Render()
		: _d3d(NULL)
		, _d3dDevice(NULL)
	{
		_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	}

	Render::~Render()
	{
		if (_d3dDevice)
			_d3dDevice->Release();
		if (_d3d)
			_d3d->Release();
	}

	bool Render::Init(Window* window)
	{
		_window = window;
		if (_window == nullptr)
			return false;

		D3DPRESENT_PARAMETERS d3dpp;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
// 		d3dpp.BackBufferWidth = size.x;
// 		d3dpp.BackBufferHeight = size.y;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		// create a device class using this information and information from the d3dpp stuct
		_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			(HWND)_window->GetHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &_d3dDevice);

		_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
// 		_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
// 		_d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
// 		_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		_d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		return true;
	}

	void Render::Clear(const Color4b& color)
	{
		_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			color.data, 1.0f, 0);
	}

	bool Render::BeginScene()
	{
		return _d3dDevice->BeginScene() == D3D_OK;
	}

	void Render::EndScene()
	{
		_d3dDevice->EndScene();
	}

	void Render::Present()
	{
		_d3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	SharedPtr<VertexBuffer> Render::CreateVertexBuffer(BufferUsage usage, unsigned int size)
	{
		LPDIRECT3DVERTEXBUFFER9 data;
		const HRESULT ret =_d3dDevice->CreateVertexBuffer(size,
			ConvertBufferUsage(usage), 0, D3DPOOL_DEFAULT, &data, NULL);
		if (ret != D3D_OK)
			return SharedPtr<VertexBuffer>::EMPTY;

		SharedPtr<VertexBuffer> buffer(new VertexBuffer());
		buffer->_data = data;
		buffer->_size = size;
		return buffer;
	}

	SharedPtr<IndexBuffer> Render::CreateIndexBuffer(BufferUsage usage, unsigned int size, IndexFormat format)
	{
		LPDIRECT3DINDEXBUFFER9 data;

		HRESULT ret = _d3dDevice->CreateIndexBuffer(size,
			ConvertBufferUsage(usage), D3DFMT_INDEX16,
			D3DPOOL_DEFAULT, &data, NULL);
		if (ret != D3D_OK)
			return SharedPtr<IndexBuffer>::EMPTY;

		SharedPtr<IndexBuffer> buffer(new IndexBuffer());
		buffer->_data = data;
		buffer->_format = format;
		buffer->_size = size;
		return buffer;
	}

	SharedPtr<VertexLayout> Render::CreateVertexLayout(const List<VertexDeclare>& declare)
	{
		return CreateVertexLayout(declare.GetData(), declare.Count());
	}

	SharedPtr<VertexLayout> Render::CreateVertexLayout(const VertexDeclare* declare, uint8_t count)
	{
		if (count == 0)
			return SharedPtr<VertexLayout>::EMPTY;

		List<D3DVERTEXELEMENT9> verts;
		verts.SetSize(count + 1);
		for (int i = 0; i < count; i++)
		{
			verts[i].Stream = 0;
			verts[i].Offset = declare[i].offset;
			verts[i].Type = ConvertVertexType(declare[i].type, declare[i].count);
			verts[i].Method = D3DDECLMETHOD_DEFAULT;
			verts[i].Usage = ConvertUsage(declare[i].usage);
			verts[i].UsageIndex = 0;
		}
		
		verts[count].Stream = 0xFF;
		verts[count].Offset = 0;
		verts[count].Type = D3DDECLTYPE_UNUSED;
		verts[count].Method = 0;
		verts[count].Usage = 0;
		verts[count].UsageIndex = 0;

		LPDIRECT3DVERTEXDECLARATION9 data;
		const auto ret = _d3dDevice->CreateVertexDeclaration(verts.GetData(), &data);
		if (ret != D3D_OK)
			return SharedPtr<VertexLayout>::EMPTY;

		SharedPtr<VertexLayout> layout(new VertexLayout());
		layout->_data = data;
		layout->_declare = List<VertexDeclare>(declare, count);
		return layout;
	}

	SharedPtr<Texture> Render::CreateTexture(const Vector2i& size, ImageFormat format)
	{
		LPDIRECT3DTEXTURE9 data;
// 		const auto ret = _d3dDevice->CreateTexture(size.x, size.y, 0, 0,
// 			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &data, NULL);
// 		if (ret != D3D_OK)
// 			return SharedPtr<Texture>::EMPTY;
		if (D3DXCreateTexture(_d3dDevice, size.x, size.y, 1,
			D3DUSAGE_DYNAMIC, ConvertFormat(format), D3DPOOL_DEFAULT, &data) < 0)
			return SharedPtr<Texture>::EMPTY;

		SharedPtr<Texture> tex(new Texture());
		tex->_data = data;
		tex->_size = size;
		return tex;
	}

	SharedPtr<Texture> Render::LoadTexture(const String& path)
	{
		LPDIRECT3DTEXTURE9 data;
		auto ret = D3DXCreateTextureFromFile(_d3dDevice, path, &data);
		if (ret != D3D_OK)
			return SharedPtr<Texture>::EMPTY;

		D3DSURFACE_DESC desc;
		ret = data->GetLevelDesc(0, &desc);
		if (ret != D3D_OK)
		{
			data->Release();
			return SharedPtr<Texture>::EMPTY;
		}

		SharedPtr<Texture> tex(new Texture());
		tex->_data = data;
		tex->_size = Vector2i(desc.Width, desc.Height);
		return tex;
	}

	bool Render::SetRenderState(RenderState state, bool val)
	{
		HRESULT ret = S_FALSE;
		switch (state)
		{
		case RenderState::Lightning:
			ret = _d3dDevice->SetRenderState(D3DRS_LIGHTING, val);
			break;

		case RenderState::ZEnable:
			ret = _d3dDevice->SetRenderState(D3DRS_ZENABLE, val);
			break;

		case RenderState::AlphaBlend:
			ret = _d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, val);
			break;

		case RenderState::AlphaTest:
			ret = _d3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, val);
			break;

		case RenderState::ScissorTest:
			ret = _d3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, val);
			break;
		}

		if (ret != D3D_OK)
			return false;

		return true;
	}


	void Render::SetCullMode(RenderCull mode)
	{
		_d3dDevice->SetRenderState(D3DRS_CULLMODE, ConvertCull(mode));
	}

	void Render::SetBlendOp(BlendOperation op)
	{
		_d3dDevice->SetRenderState(D3DRS_BLENDOP, ConvertOperation(op));
	}

	void Render::SetBlendType(BlendType type, BlendMode mode)
	{
		switch (type)
		{
		case BlendType::Source:
			_d3dDevice->SetRenderState(D3DRS_SRCBLEND, ConvertBlend(mode));
			break;

		case BlendType::Dest:
			_d3dDevice->SetRenderState(D3DRS_DESTBLEND, ConvertBlend(mode));
			break;
		}
	}

	void Render::SetScissorRect(const Recti* rect)
	{
		if (rect == nullptr)
			_d3dDevice->SetScissorRect(nullptr);
		else
		{
			::RECT in = {
				rect->pos.x, rect->pos.y,
				rect->pos.x + rect->size.x,
				rect->pos.y + rect->size.y
			};

			_d3dDevice->SetScissorRect(&in);
		}
	}

	void Render::SetTextureOp(uint8_t stage, TextureOperation op, TextureOperationValue _val)
	{
		auto val = ConvertTexOp(_val);

		switch (op)
		{
		case TSS_COLOROP:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_COLOROP, val);
			break;

		case TSS_ALPHAOP:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_ALPHAOP, val);
			break;

		case TSS_BUMPENVMAT00:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVMAT00, val);
			break;

		case TSS_BUMPENVMAT01:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVMAT01, val);
			break;

		case TSS_BUMPENVMAT10:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVMAT10, val);
			break;

		case TSS_BUMPENVMAT11:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVMAT11, val);
			break;

		case TSS_TEXCOORDINDEX:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_TEXCOORDINDEX, val);
			break;

		case TSS_BUMPENVLSCALE:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVLSCALE, val);
			break;

		case TSS_BUMPENVLOFFSET:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_BUMPENVLOFFSET, val);
			break;

		case TSS_TEXTURETRANSFORMFLAGS:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_TEXTURETRANSFORMFLAGS, val);
			break;

		case TSS_CONSTANT:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_CONSTANT, val);
			break;
		}
	}

	void Render::SetTextureArgument(uint8_t stage, TextureArgument arg, TextureArgumentValue _val)
	{
		uint32_t val;
		switch (_val)
		{
		case TEXARG_DIFFUSE: val = D3DTA_DIFFUSE; break;
		case TEXARG_CURRENT: val = D3DTA_CURRENT; break;
		case TEXARG_TEXTURE: val = D3DTA_TEXTURE; break;
		case TEXARG_TFACTOR: val = D3DTA_TFACTOR; break;
		case TEXARG_SPECULAR: val = D3DTA_SPECULAR; break;
		case TEXARG_TEMP: val = D3DTA_TEMP; break;
		case TEXARG_CONSTANT: val = D3DTA_CONSTANT; break;
		case TEXARG_COMPLEMENT: val = D3DTA_COMPLEMENT; break;
		case TEXARG_ALPHAREPLICATE: val = D3DTA_ALPHAREPLICATE; break;
			break;

		default:
			return;
			break;
		}

		switch (arg)
		{
		case TSS_COLORARG0:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG0, val);
			break;

		case TSS_COLORARG1:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG1, val);
			break;

		case TSS_COLORARG2:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG2, val);
			break;

		case TSS_ALPHAARG0:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_ALPHAARG0, val);
			break;

		case TSS_ALPHAARG1:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_ALPHAARG1, val);
			break;

		case TSS_ALPHAARG2:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_ALPHAARG2, val);
			break;

		case TSS_RESULTARG:
			_d3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG1, val);
			break;

		default:
			return;
			break;
		}
	}

	void Render::SetTextureFilter(uint8_t stage, TextureFilterTarget target, TextureFilterType _type)
	{
		D3DTEXTUREFILTERTYPE type;
		switch (_type)
		{
		case TEXFILTER_NONE: type = D3DTEXF_NONE; break;
		case TEXFILTER_POINT: type = D3DTEXF_POINT; break;
		case TEXFILTER_LINEAR: type = D3DTEXF_LINEAR; break;
		case TEXFILTER_ANISOTROPIC: type = D3DTEXF_ANISOTROPIC; break;
		case TEXFILTER_PYRAMIDALQUAD: type = D3DTEXF_PYRAMIDALQUAD; break;
		case TEXFILTER_GAUSSIANQUAD: type = D3DTEXF_GAUSSIANQUAD; break;
		default:
			return;
			break;
		}

		switch (target)
		{
		case TEXFILTERTARGET_MAG:
			_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, type);
			break;

		case TEXFILTERTARGET_MIN:
			_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, type);
			break;

		case TEXFILTERTARGET_MIP:
			_d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, type);
			break;
		}
	}

	void Render::SetTransform(TransformType transform, const Matrix4& mat)
	{
		auto state = ConvertTransformType(transform);
		_d3dDevice->SetTransform(state, (D3DXMATRIX*)&mat);
	}

	bool Render::SetTexture(uint8_t stage, Texture* texture)
	{
		if (texture == nullptr)
		{
			_d3dDevice->SetTexture(stage, nullptr);
			return true;
		}

		const auto ret = _d3dDevice->SetTexture(0, texture->_data);
		return (ret == D3D_OK);
	}

	bool Render::SetVertexLayout(VertexLayout* layout)
	{
		if (layout == nullptr || layout->_data == nullptr)
			return false;

		const auto ret = _d3dDevice->SetVertexDeclaration(layout->_data);
		return (ret == D3D_OK);
	}

	bool Render::SetVertexBuffer(uint8_t stream, VertexBuffer* buffer, uint32_t offset, uint32_t stride)
	{
		if (buffer == nullptr)
			return false;

		const auto ret = _d3dDevice->SetStreamSource(stream, buffer->_data, offset, stride);
		return (ret == D3D_OK);
	}

	bool Render::SetIndexBuffer(IndexBuffer* buffer)
	{
		if (buffer == nullptr)
			return false;

		_d3dDevice->SetIndices(buffer->_data);
		return true;
	}

	void Render::DrawPrimitive(VertexTopology type, uint32_t start, uint32_t primitiveCount)
	{
		auto primitive = ConvertPrimitiveType(type);
		_d3dDevice->DrawPrimitive(primitive, start, primitiveCount);
	}

	void Render::DrawIndexedPrimitive(VertexTopology type, int vertexStart, uint32_t minIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount)
	{
		auto primitive = ConvertPrimitiveType(type);
		_d3dDevice->DrawIndexedPrimitive(primitive, vertexStart, minIndex, numVertices, startIndex, primitiveCount);
	}
	//////////////////////////////////////////////////////////////////////////
	D3DPRIMITIVETYPE Render::ConvertPrimitiveType(VertexTopology type)
	{
		static D3DPRIMITIVETYPE convert[] = {
			D3DPT_POINTLIST, D3DPT_LINELIST, D3DPT_LINESTRIP,
			D3DPT_TRIANGLELIST, D3DPT_TRIANGLESTRIP,
		};

		return convert[type];
	}

	DWORD Render::ConvertBufferUsage(BufferUsage usage)
	{
		static DWORD convert[] = { 0, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY };
		return convert[usage];
	}

	D3DTRANSFORMSTATETYPE Render::ConvertTransformType(TransformType transform)
	{
		static D3DTRANSFORMSTATETYPE convert[] = {
			D3DTS_WORLD, D3DTS_VIEW, D3DTS_PROJECTION };

		return convert[(int)transform];
	}

	D3DDECLUSAGE Render::ConvertUsage(DeclareUsage usage)
	{
		static D3DDECLUSAGE convert[] = {
			D3DDECLUSAGE_POSITION, D3DDECLUSAGE_COLOR, D3DDECLUSAGE_TEXCOORD
		};

		return convert[usage];
	}

	D3DDECLTYPE Render::ConvertVertexType(DeclareType type, uint8_t count)
	{
		switch (type)
		{
		case VALUE_BYTE:
			break;
		case VALUE_UBYTE:
			break;
		case VALUE_SHORT:
			break;
		case VALUE_USHORT:
			break;

		case VALUE_FLOAT:
			switch (count)
			{
			case 1: return D3DDECLTYPE_FLOAT1;
			case 2: return D3DDECLTYPE_FLOAT2;
			case 3: return D3DDECLTYPE_FLOAT3;
			case 4: return D3DDECLTYPE_FLOAT4;
			}
			break;
		case VALUE_FIXED:
			break;

		case VALUE_DWORD:
			if (count == 1)
				return D3DDECLTYPE_D3DCOLOR;
			break;
		}

		return D3DDECLTYPE_UNUSED;
	}

	D3DFORMAT Render::ConvertFormat(ImageFormat format)
	{
		switch (format)
		{
		case FORMAT_A8: return D3DFMT_A8;
		case FORMAT_A8R8G8B8: return D3DFMT_A8B8G8R8;
			break;
		}

		return D3DFMT_UNKNOWN;
	}

	D3DCULL Render::ConvertCull(RenderCull cull)
	{
		switch (cull)
		{
		case CULL_NONE: return D3DCULL_NONE;
		case CULL_CW: return D3DCULL_CW;
		case CULL_CCW: return D3DCULL_CCW;
			break;
		}

		return D3DCULL_NONE;
	}

	D3DBLENDOP Render::ConvertOperation(BlendOperation op)
	{
		switch (op)
		{
		case BLENDOP_ADD: return D3DBLENDOP_ADD;
		case BLENDOP_SUB: return D3DBLENDOP_SUBTRACT;
		case BLENDOP_REVSUB: return D3DBLENDOP_REVSUBTRACT;
		case BLENDOP_MIN: return D3DBLENDOP_MIN;
		case BLENDOP_MAX: return D3DBLENDOP_MAX;
			break;
		}

		return D3DBLENDOP_ADD;
	}

	D3DBLEND Render::ConvertBlend(BlendMode mode)
	{
		switch (mode)
		{
		case BLEND_ZERO: return D3DBLEND_ZERO;
		case BLEND_ONE: return D3DBLEND_ONE;
		case BLEND_SRCCOLOR: return D3DBLEND_SRCCOLOR;
		case BLEND_INVSRCCOLOR: return D3DBLEND_INVSRCCOLOR;
		case BLEND_SRCALPHA: return D3DBLEND_SRCALPHA;
		case BLEND_INVSRCALPHA: return D3DBLEND_INVSRCALPHA;
		case BLEND_DESTALPHA: return D3DBLEND_DESTALPHA;
		case BLEND_INVDESTALPHA: return D3DBLEND_INVDESTALPHA;
		case BLEND_DESTCOLOR: return D3DBLEND_DESTCOLOR;
		case BLEND_INVDESTCOLOR: return D3DBLEND_INVDESTCOLOR;
		case BLEND_SRCALPHASAT: return D3DBLEND_SRCALPHASAT;
		case BLEND_BOTHSRCALPHA: return D3DBLEND_BOTHSRCALPHA;
		case BLEND_BOTHINVSRCALPHA: return D3DBLEND_BOTHINVSRCALPHA;
			break;
		}

		return D3DBLEND_FORCE_DWORD;
	}

	D3DTEXTUREOP Render::ConvertTexOp(TextureOperationValue val)
	{
		switch (val)
		{
		case TEXOP_DISABLE: return D3DTOP_DISABLE;
		case TEXOP_SELECTARG1: return D3DTOP_SELECTARG1;
		case TEXOP_SELECTARG2: return D3DTOP_SELECTARG2;
		case TEXOP_MODULATE: return D3DTOP_MODULATE;
		case TEXOP_MODULATE2X: return D3DTOP_MODULATE2X;
		case TEXOP_MODULATE4X: return D3DTOP_MODULATE4X;
		case TEXOP_ADD: return D3DTOP_ADD;
		case TEXOP_ADDSIGNED: return D3DTOP_ADDSIGNED;
		case TEXOP_ADDSIGNED2X: return D3DTOP_ADDSIGNED2X;
		case TEXOP_SUBTRACT: return D3DTOP_SUBTRACT;
		case TEXOP_ADDSMOOTH: return D3DTOP_ADDSMOOTH;
		case TEXOP_BLENDDIFFUSEALPHA: return D3DTOP_BLENDDIFFUSEALPHA;
		case TEXOP_BLENDTEXTUREALPHA: return D3DTOP_BLENDTEXTUREALPHA;
		case TEXOP_BLENDFACTORALPHA: return D3DTOP_BLENDFACTORALPHA;
		case TEXOP_BLENDTEXTUREALPHAPM: return D3DTOP_BLENDTEXTUREALPHAPM;
		case TEXOP_BLENDCURRENTALPHA: return D3DTOP_BLENDCURRENTALPHA;
		case TEXOP_PREMODULATE: return D3DTOP_PREMODULATE;
		case TEXOP_MODULATEALPHA_ADDCOLOR: return D3DTOP_MODULATEALPHA_ADDCOLOR;
		case TEXOP_MODULATECOLOR_ADDALPHA: return D3DTOP_MODULATECOLOR_ADDALPHA;
		case TEXOP_MODULATEINVALPHA_ADDCOLOR: return D3DTOP_MODULATEINVALPHA_ADDCOLOR;
		case TEXOP_MODULATEINVCOLOR_ADDALPHA: return D3DTOP_MODULATEINVCOLOR_ADDALPHA;
		case TEXOP_BUMPENVMAP: return D3DTOP_BUMPENVMAP;
		case TEXOP_BUMPENVMAPLUMINANCE: return D3DTOP_BUMPENVMAPLUMINANCE;
		case TEXOP_DOTPRODUCT3: return D3DTOP_DOTPRODUCT3;
		case TEXOP_MULTIPLYADD: return D3DTOP_MULTIPLYADD;
		case TEXOP_LERP: return D3DTOP_LERP;
			break;
		}

		return D3DTOP_FORCE_DWORD;
	}
}