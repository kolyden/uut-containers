#pragma once
#include "core/uutObject.h"

namespace uut
{
	class Window;
	class Render;
	class Input;
	class FileSystem;

	class Application : public Object
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

	protected:
		SharedPtr<FileSystem> _filesys;
		SharedPtr<Window> _window;
		SharedPtr<Render> _render;
		SharedPtr<Input> _input;

		virtual void OnInit() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}

	protected:
		bool _quit;
	};
}