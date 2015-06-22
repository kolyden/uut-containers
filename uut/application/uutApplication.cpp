#include "uutApplication.h"
#include "core/uutCore.h"
#include "application/uutWindow.h"
#include "video/uutVideo.h"
#include "video/uutRenderTarget.h"
#include "input/uutInput.h"

namespace uut
{
	Application::Application()
	{
		auto video = new Video();
		auto input = new Input();
		auto core = Core::GetMain();
		core->AddModule(video);
		core->AddModule(input);

		video->SetMode(IntVector2(800, 600), false);
		_target = video->CreateRenderTarget();
		video->SetTarget(_target);
	}

	void Application::Run()
	{
		auto core = Core::GetMain();
		core->Init();

		_window = core->GetModule<Window>();
		_video = core->GetModule<Video>();
		_input = core->GetModule<Input>();

		OnInit();

		while (_window->MessagePool())
		{
			OnUpdate();
			OnRender();
		}
	}
}