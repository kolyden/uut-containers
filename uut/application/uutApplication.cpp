#include "uutApplication.h"
#include "application/uutWindow.h"
#include "video/uutRender.h"
#include "input/uutInput.h"
#include "io/uutFileSystem.h"

namespace uut
{
	Application::Application()
		: _quit(false)
	{
		_filesys = new FileSystem();
		_window = new Window();
		_render = new Render();
		_input = new Input();

		_window->AddEventListener(_input);
		_window->Create(Vector2i(1024, 768));
		_render->Init(_window);
	}

	Application::~Application() = default;

	void Application::Run()
	{

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