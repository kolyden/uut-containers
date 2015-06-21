#pragma once
#include "uutObject.h"

namespace uut
{
	class Window;
	class Video;
	class Input;
	class RenderTarget;

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
		SharedPtr<RenderTarget> _target;

		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};
}