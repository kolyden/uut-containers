#include "uut.h"
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

namespace uut
{
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;
		Color4b color;
	};

	static int VERTEXFORMAT = VERTEX_XYZ | VERTEX_COLOR;

	CUSTOMVERTEX OurVertices[] =
	{
		{ -3.0f, 3.0f, -3.0f, Color4b(0, 0, 255), },
		{ 3.0f, 3.0f, -3.0f, Color4b(0, 255, 0), },
		{ -3.0f, -3.0f, -3.0f, Color4b(255, 0, 0), },
		{ 3.0f, -3.0f, -3.0f, Color4b(0, 255, 255), },
		{ -3.0f, 3.0f, 3.0f, Color4b(0, 0, 255), },
		{ 3.0f, 3.0f, 3.0f, Color4b(255, 0, 0), },
		{ -3.0f, -3.0f, 3.0f, Color4b(0, 255, 0), },
		{ 3.0f, -3.0f, 3.0f, Color4b(0, 255, 255), },
	};

	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	class MyApp : public Application
	{
	public:
		MyApp()
			: _color(Color4b::BLACK)
			, _angle(0)
		{
		}

		virtual void OnInit() override
		{
			_vbuffer = _render->CreateVertexBuffer(sizeof(CUSTOMVERTEX)* 8, VERTEXFORMAT);
			{
				auto ptr = _vbuffer->Lock();
				memcpy(ptr, OurVertices, sizeof(CUSTOMVERTEX)* 8);
				_vbuffer->Unlock();
			}

			_ibuffer = _render->CreateIndexBuffer(36 * sizeof(short), INDEX_16);
			{
				auto ptr = _ibuffer->Lock();
				memcpy(ptr, indices, sizeof(indices));
				_ibuffer->Unlock();
			}

			_time = timeGetTime();
		}

		virtual void OnUpdate() override
		{
			const DWORD curTime = timeGetTime();
			const float delta = 0.002f * (curTime - _time);
			_time = curTime;

			_angle += Math::M_HALF_PI * delta;

			if (_input->IsKey(KEY_1))
				_color = Color4b::BLACK;
			if (_input->IsKey(KEY_2))
				_color = Color4b::WHITE;
			if (_input->IsKey(KEY_3))
				_color = Color4b(100, 100, 100);
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

				auto mat = Matrix4::MakeRotateY(_angle);
				_render->SetTransform(TRANSFORM_WORLD, mat);
				_render->SetTransform(TRANSFORM_VIEW, 
					Matrix4::MakeLookAt(Vector3f(0, 0, 20), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));
				_render->SetTransform(TRANSFORM_PROJECTION,
					Matrix4::MakePerspective(Math::Deg2Rad(45), 800.0f / 600.0f, 1.0f, 100.0f));

				_render->SetVertexBuffer(_vbuffer, 0, sizeof(CUSTOMVERTEX));
				_render->SetIndexBuffer(_ibuffer);
				_render->DrawIndexedPrimitive(PRIMITIVE_TRIANGLELIST, 0, 0, 8, 0, 12);
				_render->EndScene();
			}
			_render->Present();
		}

	protected:
		Color4b _color;
		float _angle;
// 		SharedPtr<Geometry> _geom;

		DWORD _time;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
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