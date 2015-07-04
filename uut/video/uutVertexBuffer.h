#pragma once
#include "uutRenderBuffer.h"

namespace uut
{
	class VertexBuffer : public RenderBuffer
	{
		OBJECT(VertexBuffer, RenderBuffer)
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		virtual void* Lock() override;
		virtual void Unlock() override;

	protected:
		LPDIRECT3DVERTEXBUFFER9 _data;

		friend class Render;
	};
}