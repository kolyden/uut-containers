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
			_window->GetHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &_d3dDevice);

		_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
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

	SharedPtr<Texture> Render::CreateTexture(const Vector2i& size)
	{
		LPDIRECT3DTEXTURE9 data;
		const auto ret = _d3dDevice->CreateTexture(size.x, size.y, 0, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &data, NULL);
		if (ret != D3D_OK)
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

	void Render::SetRenderState(RenderState state, bool val)
	{
		auto rs = ConvertRenderState(state);
		_d3dDevice->SetRenderState(rs, val ? TRUE : FALSE);
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

	D3DRENDERSTATETYPE Render::ConvertRenderState(RenderState state)
	{
		static D3DRENDERSTATETYPE convert[] = {
			D3DRS_LIGHTING, D3DRS_ZENABLE,
		};
		return convert[(int)state];
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

}