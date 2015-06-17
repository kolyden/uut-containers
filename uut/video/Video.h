#pragma once
#include "core/Object.h"
#include "VideoDefs.h"
#include "Color.h"

namespace uut
{
	class Window;
	class Texture;
	class Shader;
	class VideoBuffer;
	class BufferLayout;

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

		SharedPtr<Shader> CreateShaderFromMemory(const char* code, int size = -1);
		SharedPtr<Shader> CreateShaderFromFile(const wchar_t* filepath);

		SharedPtr<VideoBuffer> CreateBuffer(unsigned int size);

		bool SetShader(Shader* shader);
		bool SetLayout(BufferLayout* layout);
		bool SetBuffer(VideoBuffer* buffer, unsigned int stride, unsigned int offset);
		bool SetTopology(VertexTopology topology);

		bool Draw(unsigned int count, unsigned int start);

	protected:
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
		ID3D11RenderTargetView* _renderTarget;

		std::unique_ptr<Window> _window;
		std::shared_ptr<Texture> _backBuffer;

		bool ParseReturn(HRESULT hret);

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}