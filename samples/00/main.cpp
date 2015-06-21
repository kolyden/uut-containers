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
			_geom->SetVertices({ Vector3(-0.5f, -0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f) });
			_geom->SetColors({ Color(1.0f, 0.0f, 0.0f), Color(0.0f, 1.0f, 0.0f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 1.0f, 0.0f) });
			_geom->SetIndexes({ 0, 1, 2, 0, 2, 3 });
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