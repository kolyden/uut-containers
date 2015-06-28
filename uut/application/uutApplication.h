#pragma once
#include "core/uutObject.h"

namespace uut
{
	class Window;
	class Render;
	class Input;

	class Application : public Object
	{
		OBJECT(Application, Object)
	public:
		Application();

		void Run();
		void Quit();

	protected:
		WeakPtr<Window> _window;
		WeakPtr<Render> _render;
		WeakPtr<Input> _input;
// 		SharedPtr<RenderTarget> _target;

		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}

	protected:
		bool _quit;
	};
}