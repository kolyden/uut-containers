#pragma once
#include "imgui/imgui.h"
#include "core/uutModule.h"
#include "application/uutEventListener.h"

namespace uut
{
	class Render;
	class Window;
	class Texture;
	class Input;
	class VertexBuffer;
	class IndexBuffer;
	class VertexLayout;

	class Gui : public Module, public EventListener
	{
		OBJECT(Gui, Module)
	public:
		Gui();

		void Update(float deltaTime);
		void Draw();

	protected:
		WeakPtr<Render> _render;
		WeakPtr<Window> _window;
		WeakPtr<Input> _input;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
		SharedPtr<VertexLayout> _layout;
		SharedPtr<Texture> _texture;

		virtual void OnInit() override;
		virtual void OnDone() override;
		virtual void OnKeyDown(EKeycode code) override;
		virtual void OnKeyUp(EKeycode code) override;
		virtual void OnChar(uint32_t c) override;

		virtual void OnMouseDown(int button) override;
		virtual void OnMouseUp(int button) override;
		virtual void OnMouseMove(const Vector2i& pos) override;
		virtual void OnMouseWheel(float delta) override;

		void DrawList(ImDrawData* draw_data);

		static void DrawListStatic(ImDrawData* draw_data);
	};
}