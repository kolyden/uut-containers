#pragma once
#include "core/uutModule.h"
#include "uutVideoDefs.h"
#include "uutColor.h"
#include "math/uutVector2.h"

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

		bool SetMode(const IntVector2& size, bool fullscreen);
		const IntVector2& GetSize() const { return _size; }

		ID3D11Device* GetDevice() const { return _device; }
		ID3D11DeviceContext* GetContext() const { return _context; }

		void Present();

		SharedPtr<RenderTarget> CreateRenderTarget();
		SharedPtr<Shader> CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size = -1);

		SharedPtr<VideoBuffer> CreateBuffer(BufferType type, BufferUsage usage, unsigned int size);

		bool SetTarget(RenderTarget* target);
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
		IntVector2 _size;

		SharedPtr<Window> _window;

		bool ParseReturn(HRESULT hret);
	};
}