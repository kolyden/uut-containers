#include "uutRender.h"
#include "application/uutWindow.h"
#include "uutVertexBuffer.h"

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

	bool Render::Init(Window* window, const Vector2i& size)
	{
		_window = window;
		if (_window == nullptr)
			return false;

		D3DPRESENT_PARAMETERS d3dpp;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = _window->GetHWND();
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth = size.x;
		d3dpp.BackBufferHeight = size.y;

		// create a device class using this information and information from the d3dpp stuct
		_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			_window->GetHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &_d3dDevice);

		_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		return true;
	}

	void Render::Clear(const Color4b& color)
	{
		_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
			D3DCOLOR_RGBA(color.r, color.g, color.b, color.a), 1.0f, 0);
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

	SharedPtr<VertexBuffer> Render::CreateVertexBuffer(unsigned int size, int format)
	{
		LPDIRECT3DVERTEXBUFFER9 data;
		DWORD fvf = ConvertFormat(format);
		HRESULT ret =_d3dDevice->CreateVertexBuffer(size, 0,
			fvf, D3DPOOL_MANAGED, &data, NULL);
		if (ret != D3D_OK)
			return SharedPtr<VertexBuffer>::EMPTY;

		SharedPtr<VertexBuffer> buffer(new VertexBuffer());
		buffer->_data = data;
		buffer->_format = format;
		return buffer;
	}

	void Render::SetRenderState(ERenderState state, bool val)
	{
		auto rs = ConvertRenderState(state);
		_d3dDevice->SetRenderState(rs, val ? TRUE : FALSE);
	}

	void Render::SetTransform(ETransformType transform, const Matrix4& mat)
	{
		auto state = ConvertTransformType(transform);
		_d3dDevice->SetTransform(state, (D3DXMATRIX*)&mat);
	}

	void Render::SetVertexFormat(int format)
	{
		DWORD fvf = ConvertFormat(format);
		_d3dDevice->SetFVF(fvf);
	}

	bool Render::SetVertexBuffer(VertexBuffer* buffer, uint32_t offset, uint32_t stride)
	{
		if (buffer == nullptr)
			return false;
		_d3dDevice->SetStreamSource(0, buffer->_data, offset, stride);
		return true;
	}

	void Render::DrawPrimitive(EPrimitiveType type, uint32_t start, uint32_t primitiveCount)
	{
		auto primitive = ConvertPrimitiveType(type);
		_d3dDevice->DrawPrimitive(primitive, start, primitiveCount);
	}

	//////////////////////////////////////////////////////////////////////////
	DWORD Render::ConvertFormat(unsigned int format)
	{
		DWORD fvf = 0;
		if (format & VERTEX_XYZ)
			fvf |= D3DFVF_XYZ;
		if (format & VERTEX_XYZRHW)
			fvf |= D3DFVF_XYZRHW;
		if (format & VERTEX_COLOR)
			fvf |= D3DFVF_DIFFUSE;
		if (format & VERTEX_TEXCOORDS0)
			fvf |= D3DFVF_TEX0;

		return fvf;
	}

	D3DPRIMITIVETYPE Render::ConvertPrimitiveType(EPrimitiveType type)
	{
		static D3DPRIMITIVETYPE convert[] = {
			D3DPT_POINTLIST, D3DPT_LINELIST, D3DPT_LINESTRIP,
			D3DPT_TRIANGLELIST, D3DPT_TRIANGLESTRIP,
		};

		return convert[type];
	}

	D3DTRANSFORMSTATETYPE Render::ConvertTransformType(ETransformType transform)
	{
		static D3DTRANSFORMSTATETYPE convert[] = {
			D3DTS_WORLD, D3DTS_VIEW, D3DTS_PROJECTION };

		return convert[transform];
	}

	D3DRENDERSTATETYPE Render::ConvertRenderState(ERenderState state)
	{
		static D3DRENDERSTATETYPE convert[] = {
			D3DRS_LIGHTING
		};
		return convert[state];
	}
}