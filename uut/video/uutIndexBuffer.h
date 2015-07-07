#pragma once
#include "uutRenderBuffer.h"

namespace uut
{
	class IndexBuffer : public RenderBuffer
	{
		OBJECT(IndexBuffer, RenderBuffer)
	public:
		IndexBuffer();
		virtual ~IndexBuffer();

		virtual void* Lock(unsigned int offset, unsigned int size, bool discard = false) override;
		virtual void Unlock() override;
		virtual bool Update(const void* data, unsigned int offset, unsigned int size) override;

	protected:
		LPDIRECT3DINDEXBUFFER9 _data;
		IndexFormat _format;

		friend class Render;
	};
}