#include "uutApplication.h"
#include "uutCore.h"
#include "video/uutVideo.h"
#include "video/uutWindow.h"
#include "input/uutInput.h"

namespace uut
{
	Application::Application()
	{
		auto video = new Video();
		auto core = Core::GetMain();
		core->AddModule(video);

		video->SetMode(800, 600, false);
	}

	void Application::Run()
	{
		auto core = Core::GetMain();
		_window = core->GetModule<Window>();
		_video = core->GetModule<Video>();
		_input = core->GetModule<Input>();

		OnInit();

		while (_video->MessagePool())
		{
			OnUpdate();
			OnRender();
		}
	}
}