#include "uut.h"
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

namespace uut
{
	class MyApp : public Application
	{
	public:
		struct cbPerObject
		{
			XMMATRIX  WVP;
		};

		MyApp()
			: _color(0.0f, 0.2f, 0.4f)
			, _updateCamera(true)
		{
		}

		virtual void OnInit() override
		{
			_geom = new Geometry(_video);
			_geom->SetVertices({ Vector3(-0.5f, -0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f) });
			_geom->SetColors({ Color(1.0f, 0.0f, 0.0f), Color(0.0f, 1.0f, 0.0f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f) });
			_geom->SetIndexes({ 0, 1, 2, 0, 2, 3 });
			_geom->Generate();

			_cbuffer = _video->CreateBuffer(BufferType::Constant, BufferUsage::Default, sizeof(cbPerObject));
			_camPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
			_camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			_camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

			const float aspect = static_cast<float>(_video->GetSize().x) / _video->GetSize().y;
			_camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, aspect, 1.0f, 1000.0f);

			_time = timeGetTime();
		}

		virtual void OnUpdate() override
		{
			const DWORD curTime = timeGetTime();
			const float delta = 0.001f * (curTime - _time);
			_time = curTime;

			if (_input->IsKey(KEY_1))
				_color = Color::WHITE;
			if (_input->IsKey(KEY_2))
				_color = Color::BLACK;

			if (_input->IsKey(KEY_RIGHT))
			{
				const float amount = 0.1f * delta;
				_camPosition -= XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
				_camTarget -= XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
				_updateCamera = true;
			}

			if (_input->IsKey(KEY_LEFT))
			{
				const float amount = 0.1f * delta;
				_camPosition += XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
				_camTarget += XMVectorSet(amount, 0.0f, 0.0f, 0.0f);
				_updateCamera = true;
			}

			if (_updateCamera)
			{
				_updateCamera = false;
				_camView = XMMatrixLookAtLH(_camPosition, _camTarget, _camUp);
			}
		}

		virtual void OnRender() override
		{
			_target->Clear(_color);

			_World = XMMatrixIdentity();
			_WVP = _World * _camView * _camProjection;

			_cbPerObj.WVP = XMMatrixTranspose(_WVP);
			_video->GetContext()->UpdateSubresource(_cbuffer->GetData(), 0, NULL, &_cbPerObj, 0, 0);
			_video->SetConstantBuffer(_cbuffer);

			_geom->Draw();
			_video->Present();
		}

	protected:
		Color _color;
		SharedPtr<Geometry> _geom;
		SharedPtr<VideoBuffer> _cbuffer;
		DWORD _time;

		XMMATRIX _WVP;
		XMMATRIX _World;
		XMMATRIX _camView;
		XMMATRIX _camProjection;

		XMVECTOR _camPosition;
		XMVECTOR _camTarget;
		XMVECTOR _camUp;
		cbPerObject _cbPerObj;
		bool _updateCamera;
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