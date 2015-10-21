#include "uut.h"
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

namespace uut
{
	class MyApp : public Application
	{
	public:
		MyApp()
			: _color(Color4b::BLACK)
			, _angle(0)
			, _drag(false)
		{
			_camera.SetPosition(Vector3f(0, 0, -20));
		}

		virtual void OnInit() override
		{
			_geom = new Geometry(_render);
			_geom->SetVertices({
				Vector3f(-3.0f, 3.0f, -3.0f), Vector3f(3.0f, 3.0f, -3.0f),
				Vector3f(-3.0f, -3.0f, -3.0f), Vector3f(3.0f, -3.0f, -3.0f),
				Vector3f(-3.0f, 3.0f, 3.0f), Vector3f(3.0f, 3.0f, 3.0f),
				Vector3f(-3.0f, -3.0f, 3.0f), Vector3f(3.0f, -3.0f, 3.0f)
			});
			_geom->SetColors({
				Color4b(0, 0, 255), Color4b(0, 255, 0),
				Color4b(255, 0, 0), Color4b(0, 255, 255),
				Color4b(0, 0, 255), Color4b(255, 0, 0),
				Color4b(0, 255, 0), Color4b(0, 255, 255)
			});
			_geom->SetIndexes({
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
			});
			_geom->SetUV(List<Vector2f>(8, Vector2f::ZERO));
			_geom->Generate();

			_graphics = new Graphics(_render);

			_time = timeGetTime();
		}

		virtual void OnUpdate() override
		{
			const DWORD curTime = timeGetTime();
			const float delta = 0.002f * (curTime - _time);
			_time = curTime;

			_angle += Math::M_HALF_PI * delta;

			if (_drag)
			{
				if (!_input->IsMouseButton(0))
					_drag = false;
				else
				{
					const auto pos = _input->GetMousePos();
					const Vector2i deltapos = pos - _dragPos;
					_dragPos = pos;
					_camera.Move(Vector3f(delta * deltapos.x, 0, delta * deltapos.y));
				}
			}
			else if (_input->IsMouseButton(0))
			{
				_drag = true;
				_dragPos = _input->GetMousePos();
			}

			if (_input->IsKey(KEY_1))
				_color = Color4b::BLACK;
			if (_input->IsKey(KEY_2))
				_color = Color4b::WHITE;
			if (_input->IsKey(KEY_3))
				_color = Color4b(100, 100, 100);
			if (_input->IsKey(KEY_ESCAPE))
				Quit();

			const float amount = 10.0f;
			if (_input->IsKey(KEY_RIGHT))
				_camera.Move(Vector3f(+amount * delta, 0, 0));
// 				_camPosition.x += amount * delta;

			if (_input->IsKey(KEY_LEFT))
				_camera.Move(Vector3f(-amount * delta, 0, 0));
// 				_camPosition.x -= amount * delta;
		}

		virtual void OnRender() override
		{
			_render->Clear(_color);
			if (_render->BeginScene())
			{
				auto mat = Matrix4::MakeRotateY(_angle);
				_render->SetTransform(TransformType::World, mat);
				_render->SetTransform(TransformType::View, _camera.Generate());
				_render->SetTransform(TransformType::Projection,
					Matrix4::MakePerspective(Math::Deg2Rad(45), 800.0f / 600.0f, 1.0f, 100.0f));

				_graphics->DrawQuad(
					Vertex(-3.0f, 3.0f, -3.0f),
					Vertex(3.0f, 3.0f, -3.0f),
					Vertex(-3.0f, -3.0f, -3.0f),
					Vertex(3.0f, -3.0f, -3.0f));
				_graphics->Flush();

// 				_geom->Draw();
				_render->EndScene();
			}
			_render->Present();
		}

	protected:
		Color4b _color;
		float _angle;
		SharedPtr<Geometry> _geom;

		DWORD _time;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
		SharedPtr<Graphics> _graphics;

		Camera _camera;
		bool _drag;
		Vector2i _dragPos;
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