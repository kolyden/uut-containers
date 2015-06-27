#include "uutApplication.h"
#include "core/uutCore.h"
#include "application/uutWindow.h"
#include "video/uutVideo.h"
#include "video/uutRenderTarget.h"
#include "input/uutInput.h"

namespace uut
{
	Application::Application()
		: _quit(false)
	{
		auto video = new Video();
		auto input = new Input();
		auto core = Core::GetMain();
		core->AddModule(video);
		core->AddModule(input);

		video->SetMode(Vector2i(800, 600), false);
// 		_target = video->GetBackBuffer();
// 		video->SetTarget(_target);
	}

	void Application::Run()
	{
		auto core = Core::GetMain();
		core->Init();

		_window = core->GetModule<Window>();
		_video = core->GetModule<Video>();
		_input = core->GetModule<Input>();

		OnInit();

		while (!_quit && _window->MessagePool())
		{
			OnUpdate();
			OnRender();
		}
	}

	void Application::Quit()
	{
		_quit = true;
	}
}