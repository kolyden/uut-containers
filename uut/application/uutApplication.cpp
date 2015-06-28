#include "uutApplication.h"
#include "core/uutCore.h"
#include "application/uutWindow.h"
#include "video/uutRender.h"
#include "input/uutInput.h"

namespace uut
{
	Application::Application()
		: _quit(false)
	{
		auto window = new Window();
		auto render = new Render();
		auto input = new Input();
		auto core = Core::GetMain();
		core->AddModule(window);
		core->AddModule(render);
		core->AddModule(input);

		const Vector2i size(800, 600);
		window->Create(size);
		render->Init(window, size);
// 		_target = video->GetBackBuffer();
// 		video->SetTarget(_target);
	}

	void Application::Run()
	{
		auto core = Core::GetMain();
		core->Init();

		_window = core->GetModule<Window>();
		_render = core->GetModule<Render>();
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