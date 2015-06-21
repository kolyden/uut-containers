#pragma once
#include "uutObject.h"

namespace uut
{
	class Window;
	class Video;
	class Input;

	class Application : public Object
	{
		OBJECT(Application, Object)
	public:
		Application();

		void Run();

	protected:
		WeakPtr<Window> _window;
		WeakPtr<Video> _video;
		WeakPtr<Input> _input;

		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};
}