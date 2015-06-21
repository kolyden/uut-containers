#pragma once
#include "core/uutModule.h"
#include "uutVideoDefs.h"
#include "uutColor.h"

namespace uut
{
	class Window;
	class Texture;
	class RenderTarget;
	class Shader;
	class VideoBuffer;
	class VertexBuffer;
	class IndexBuffer;

	class Video : public Module
	{
		OBJECT(Video, Module)
	public:
		Video();
		virtual ~Video();

		bool SetMode(int width, int height, bool fullscreen);

		ID3D11Device* GetDevice() const { return _device; }
		ID3D11DeviceContext* GetContext() const { return _context; }

		void Present();

		SharedPtr<RenderTarget> CreateRenderTarget();
		SharedPtr<Shader> CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size = -1);

		SharedPtr<VideoBuffer> CreateBuffer(BufferType type, BufferUsage usage, unsigned int size);

		bool SetTarget(RenderTarget* target);
		bool SetShader(Shader* shader);
		bool SetBuffer(VideoBuffer* buffer, unsigned int stride, unsigned int offset);
		bool SetTopology(VertexTopology topology);

		bool Draw(unsigned int count, unsigned int start);

		Window* GetWindow() const;

	protected:
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;

		SharedPtr<Window> _window;
// 		SharedPtr<RenderTarget> _renderTarget;

		bool ParseReturn(HRESULT hret);
	};
}