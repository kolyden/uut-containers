#include "uut.h"
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

namespace uut
{
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
		DWORD color;    // from the D3DFVF_DIFFUSE flag
	};

	static int VERTEXFORMAT = VERTEX_XYZRHW | VERTEX_COLOR;

	CUSTOMVERTEX OurVertices[] =
	{
		{ 320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
	};

	class MyApp : public Application
	{
	public:
		MyApp()
			: _color(0, 50, 200)
		{
		}

		virtual void OnInit() override
		{
			_vbuffer = _render->CreateVertexBuffer(sizeof(CUSTOMVERTEX)* 3, VERTEXFORMAT);
			auto ptr = _vbuffer->Lock();
			memcpy(ptr, OurVertices, sizeof(CUSTOMVERTEX)* 3);
			_vbuffer->Unlock();

// 			_depth = _video->CreateDepthTexture();
// 			_video->SetTarget(_video->GetBackBuffer(), _depth);
// 
// 			_geom = new Geometry(_video);
// 			_geom->SetVertices({ Vector3(-0.5f, -0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f) });
// 			_geom->SetColors({ Color(1.0f, 0.0f, 0.0f), Color(0.0f, 1.0f, 0.0f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f) });
// 			_geom->SetIndexes({ 0, 1, 2, 0, 2, 3 });
// 			_geom->Generate();
// 
// 			_cbuffer = _video->CreateBuffer(BufferType::Constant, BufferUsage::Default, sizeof(cbPerObject));
// 			_camPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
// 			_camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
// 			_camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
// 
// 			const float aspect = static_cast<float>(_video->GetSize().x) / _video->GetSize().y;
// 			_camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, aspect, 1.0f, 1000.0f);

			_time = timeGetTime();
		}

		virtual void OnUpdate() override
		{
			const DWORD curTime = timeGetTime();
			const float delta = 0.001f * (curTime - _time);
			_time = curTime;

			if (_input->IsKey(KEY_1))
				_color = Color4b::WHITE;
			if (_input->IsKey(KEY_2))
				_color = Color4b::BLACK;
			if (_input->IsKey(KEY_ESCAPE))
				Quit();

// 			if (_input->IsKey(KEY_RIGHT))
// 			{
// 				const float amount = 0.1f * delta;
// 				_camPosition -= XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
// 				_camTarget -= XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
// 				_updateCamera = true;
// 			}

// 			if (_input->IsKey(KEY_LEFT))
// 			{
// 				const float amount = 0.1f * delta;
// 				_camPosition += XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
// 				_camTarget += XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
// 				_updateCamera = true;
// 			}

// 			if (_updateCamera)
// 			{
// 				_updateCamera = false;
// 				_camView = XMMatrixLookAtLH(_camPosition, _camTarget, _camUp);
// 			}
		}

		virtual void OnRender() override
		{
			_render->Clear(_color);
			if (_render->BeginScene())
			{
				_render->SetVertexFormat(VERTEXFORMAT);
				_render->SetVertexBuffer(_vbuffer, 0, sizeof(CUSTOMVERTEX));
				_render->DrawPrimitive(PRIMITIVE_TRIANGLELIST, 0, 1);
				_render->EndScene();
			}
			_render->Present();
// 			_video->GetBackBuffer()->Clear(_color);
// 
// 			_World = XMMatrixIdentity();
// 			_WVP = _World * _camView * _camProjection;
// 
// 			_cbPerObj.WVP = XMMatrixTranspose(_WVP);
// 			_video->GetContext()->UpdateSubresource(_cbuffer->GetData(), 0, NULL, &_cbPerObj, 0, 0);
// 			_video->SetConstantBuffer(_cbuffer);
// 
// 			_geom->Draw();
// 			_video->Present();
		}

	protected:
		Color4b _color;
// 		SharedPtr<Geometry> _geom;
// 		SharedPtr<VideoBuffer> _cbuffer;
// 		SharedPtr<DepthTexture> _depth;
		DWORD _time;
		SharedPtr<VertexBuffer> _vbuffer;

// 		XMMATRIX _WVP;
// 		XMMATRIX _World;
// 		XMMATRIX _camView;
// 		XMMATRIX _camProjection;
// 
// 		XMVECTOR _camPosition;
// 		XMVECTOR _camTarget;
// 		XMVECTOR _camUp;
// 		cbPerObject _cbPerObj;
// 		bool _updateCamera;
	};
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	uut::MyApp app;
	app.Run();

	return 0;
}