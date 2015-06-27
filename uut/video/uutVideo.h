#pragma once
#include "core/uutModule.h"
#include "uutVideoDefs.h"
#include "uutColor.h"
#include "math/uutVector2.h"

namespace uut
{
	class Window;
	class Texture;
	class DepthTexture;
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

		bool SetMode(const Vector2i& size, bool fullscreen);
		const Vector2i& GetSize() const { return _size; }

		ID3D11Device* GetDevice() const { return _device; }
		ID3D11DeviceContext* GetContext() const { return _context; }
		RenderTarget* GetBackBuffer() const { return _backBuffer; }

		void Present();
		
		SharedPtr<DepthTexture> CreateDepthTexture();
		SharedPtr<Shader> CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size = -1);

		SharedPtr<VideoBuffer> CreateBuffer(BufferType type, BufferUsage usage, unsigned int size);

		bool SetTarget(RenderTarget* target, DepthTexture* depth = nullptr);
		bool SetShader(Shader* shader);
		bool SetVertexBuffer(VideoBuffer* buffer, unsigned int stride, unsigned int offset);
		bool SetIndexBuffer(VideoBuffer* buffer, IndexType type, unsigned int offset);
		bool SetConstantBuffer(VideoBuffer* buffer);
		bool SetTopology(VertexTopology topology);

		bool Draw(unsigned int count, unsigned int start);
		bool DrawIndexed(unsigned int count, unsigned int start, unsigned int baseVertex);

		Window* GetWindow() const;

	protected:
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _context;
		Vector2i _size;

		SharedPtr<Window> _window;
		SharedPtr<RenderTarget> _backBuffer;

		bool ParseReturn(HRESULT hret);
	};
}