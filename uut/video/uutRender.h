#pragma once
#include "core/uutModule.h"
#include "math/uutVector2.h"
#include "uutVideoDefs.h"
#include "uutColor.h"

namespace uut
{
	class Window;
	class VertexBuffer;

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

		SharedPtr<VertexBuffer> CreateVertexBuffer(unsigned int size, int format);

		void SetVertexFormat(int format);
		bool SetVertexBuffer(VertexBuffer* buffer, uint32_t offset, uint32_t stride);

		void DrawPrimitive(EPrimitiveType type, uint32_t start, uint32_t primitiveCount);

	protected:
		SharedPtr<Window> _window;
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3dDevice;

		static DWORD ConvertFormat(unsigned int format);
		static D3DPRIMITIVETYPE ConvertPrimitiveType(EPrimitiveType type);
	};
}