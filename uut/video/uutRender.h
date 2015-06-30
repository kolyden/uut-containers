#pragma once
#include "core/uutModule.h"
#include "math/uutVector2.h"
#include "math/uutMatrix.h"
#include "math/uutColor.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Window;
	class VertexBuffer;
	class IndexBuffer;
	class Texture;

	class Render : public Module
	{
		OBJECT(Render, Module)
	public:
		Render();
		virtual ~Render();

		LPDIRECT3DDEVICE9 GetDevice() const { return _d3dDevice; }

		bool Init(Window* window, const Vector2i& size);
		void Clear(const Color4b& color);
		bool BeginScene();
		void EndScene();
		void Present();

		SharedPtr<VertexBuffer> CreateVertexBuffer(unsigned int size, int format);
		SharedPtr<IndexBuffer> CreateIndexBuffer(unsigned int size, EIndexFormat format);
		SharedPtr<Texture> CreateTexture(const Vector2i& size);

		void SetRenderState(ERenderState state, bool val);
		void SetTransform(ETransformType transform, const Matrix4& mat);
		void SetVertexFormat(int format);
		bool SetVertexBuffer(VertexBuffer* buffer, uint32_t offset, uint32_t stride);
		bool SetIndexBuffer(IndexBuffer* buffer);

		void DrawPrimitive(EPrimitiveType type, uint32_t start, uint32_t primitiveCount);
		void DrawIndexedPrimitive(EPrimitiveType type, int vertexStart,
			uint32_t minIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount);

	protected:
		SharedPtr<Window> _window;
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3dDevice;

		static DWORD ConvertFormat(unsigned int format);
		static D3DPRIMITIVETYPE ConvertPrimitiveType(EPrimitiveType type);
		static D3DTRANSFORMSTATETYPE ConvertTransformType(ETransformType transform);
		static D3DRENDERSTATETYPE ConvertRenderState(ERenderState state);
	};
}