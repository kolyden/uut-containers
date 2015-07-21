#pragma once
#include "imgui/imgui.h"
#include "core/uutModule.h"

namespace uut
{
	class Render;
	class Window;
	class Texture;
	class Input;
	class VertexBuffer;
	class IndexBuffer;
	class VertexLayout;

	class Gui : public Module
	{
		OBJECT(Gui, Module)
	public:
		Gui();

		void NewFrame();
		void Draw();

	protected:
		WeakPtr<Render> _render;
		WeakPtr<Window> _window;
		WeakPtr<Input> _input;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
		SharedPtr<VertexLayout> _layout;
		SharedPtr<Texture> _texture;

		unsigned long _time;

		virtual void OnInit() override;

		void DrawList(ImDrawData* draw_data);

		static void DrawListStatic(ImDrawData* draw_data);
	};
}