#include "uutApplication.h"
#include "core/uutCore.h"
#include "application/uutWindow.h"
#include "video/uutRender.h"
#include "input/uutInput.h"
#include "io/uutFileSystem.h"

namespace uut
{
	Application::Application()
		: _quit(false)
	{
		auto window = new Window();
		auto render = new Render();
		auto input = new Input();
		auto fsys = new FileSystem();

		auto core = Core::GetMain();
		core->AddModule(window);
		core->AddModule(render);
		core->AddModule(input);
		core->AddModule(fsys);

		window->Create(Vector2i(1024, 768));
		render->Init(window);
	}

	void Application::Run()
	{
		auto core = Core::GetMain();
		core->Init();

		_window = core->GetModule<Window>();
		_render = core->GetModule<Render>();
		_input = core->GetModule<Input>();
		_filesys = core->GetModule<FileSystem>();

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