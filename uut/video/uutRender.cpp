#include "uutRender.h"
#include "application/uutWindow.h"

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

		// create a device class using this information and information from the d3dpp stuct
		_d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			_window->GetHWND(),
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&_d3dDevice);

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
}