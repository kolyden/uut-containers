#pragma once
#include "VideoDefs.h"
#include "Color.h"

namespace uut
{
	class Window;
	class Texture;
	class Shader;
	class VideoBuffer;
	class BufferLayout;

	class Video
	{
	public:
		Video();
		virtual ~Video();

		bool SetMode(int width, int height, bool fullscreen);
		bool MessagePool();

		void ClearTarget(const Color& color);
		void Present();

		std::shared_ptr<Shader> CreateShaderFromMemory(const char* code, ShaderType type);
		std::shared_ptr<Shader> CreateShaderFromFile(const char* code, ShaderType type);
		std::shared_ptr<VideoBuffer> CreateBuffer(unsigned int size);
		std::shared_ptr<BufferLayout> CreateLayout(D3D11_INPUT_ELEMENT_DESC* desc, BYTE count, std::shared_ptr<Shader> shader);

		bool UpdateBuffer(std::shared_ptr<VideoBuffer> buffer, const void* ptr, unsigned int size);

		bool SetShader(ShaderType type, std::shared_ptr<Shader> shader);
		bool SetLayout(std::shared_ptr<BufferLayout> layout);
		bool SetBuffer(std::shared_ptr<VideoBuffer> buffer, unsigned int stride, unsigned int offset);
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