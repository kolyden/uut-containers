#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"

namespace uut
{
	class RenderBuffer : public Object
	{
	public:
		RenderBuffer();

		virtual void* Lock(unsigned int offset, unsigned int size, bool discard = false) = 0;
		virtual void Unlock() = 0;
		virtual bool Update(const void* data, unsigned int offset, unsigned int size) = 0;

		unsigned int GetSize() const { return _size; }

	protected:
		bool _locked;
		unsigned int _size;
	};
}