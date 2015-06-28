#pragma once
#include "core/uutModule.h"
#include "math/uutVector2.h"
#include "uutVideoDefs.h"
#include "uutColor.h"

namespace uut
{
	class Window;

	class Render : public Module
	{
		OBJECT(Render, Module)
	public:
		Render();
		virtual ~Render();

		bool Init(Window* window, const Vector2i& size);
		void Clear(const Color4b& color);
		bool BeginScene();
		void EndScene();
		void Present();

	protected:
		SharedPtr<Window> _window;
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3dDevice;
	};
}