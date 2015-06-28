#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"

namespace uut
{
	class VertexBuffer : public Object
	{
		OBJECT(VertexBuffer, Object)
	public:
		VertexBuffer();
		virtual ~VertexBuffer();

		void* Lock();
		void Unlock();

	protected:
		LPDIRECT3DVERTEXBUFFER9 _data;
		int _format;
		bool _locked;

		friend class Render;
	};
}