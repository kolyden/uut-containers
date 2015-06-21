#include "uut.h"

namespace uut
{
	class MyApp : public Application
	{
	public:
		MyApp()
			: _color(0.0f, 0.2f, 0.4f)
		{
		}

		virtual void OnInit() override
		{
			_geom = new Geometry(_video);
			_geom->SetVertices({ uut::Vector3(0.00f, 0.5f, 0.0f), uut::Vector3(0.45f, -0.5f, 0.0f), uut::Vector3(-0.45f, -0.5f, 0.0f) });
			_geom->SetColors({ uut::Color(1.0f, 0.0f, 0.0f, 1.0f), uut::Color(0.0f, 1.0f, 0.0f, 1.0f), uut::Color(0.0f, 0.0f, 1.0f, 1.0f) });
			_geom->Generate();
		}

		virtual void OnUpdate() override
		{
			if (_input->IsKey(KEY_1))
				_color = Color::WHITE;
			if (_input->IsKey(KEY_2))
				_color = Color::BLACK;
		}

		virtual void OnRender() override
		{
			_target->Clear(_color);
			_geom->Draw();
			_video->Present();
		}

	protected:
		Color _color;
		SharedPtr<Geometry> _geom;
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