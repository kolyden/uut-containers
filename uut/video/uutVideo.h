#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"
#include "uutColor.h"

namespace uut
{
	class Window;
	class Texture;
	class Shader;
	class RenderBuffer;
	class VertexLayout;

	class Video : public Object
	{
	public:
		Video();
		virtual ~Video();

		bool SetMode(int width, int height, bool fullscreen);
		bool MessagePool();

		ID3D11Device* GetDevice() const { return _device; }
		ID3D11DeviceContext* GetContext() const { return _context; }

		void ClearTarget(const Color& color);
		void Present();

		SharedPtr<Shader> CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size = -1);

		SharedPtr<RenderBuffer> CreateBuffer(unsigned int size);

		bool SetShader(Shader* shader);
		bool SetBuffer(RenderBuffer* buffer, unsigned int stride, unsigned int offset);
		bool SetTopology(VertexTopology topology);

		bool Draw(unsigned int count, unsigned int start);

		Window* GetWindow() const;

	protected:
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
		ID3D11RenderTargetView* _renderTarget;

		SharedPtr<Window> _window;
		SharedPtr<Texture> _backBuffer;

		bool ParseReturn(HRESULT hret);

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}