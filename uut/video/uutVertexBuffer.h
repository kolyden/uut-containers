#pragma once
#include "uutRenderBuffer.h"

namespace uut
{
	class VertexBuffer : public RenderBuffer
	{
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		virtual void* Lock(unsigned int offset, unsigned int size, bool discard = false) override;
		virtual void Unlock() override;
		virtual bool Update(const void* data, unsigned int offset, unsigned int size) override;

	protected:
		LPDIRECT3DVERTEXBUFFER9 _data;

		friend class Render;
	};
}