#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"

namespace uut
{
	class RenderBuffer : public Object
	{
		OBJECT(RenderBuffer, Object)
	public:
		RenderBuffer();

		virtual void* Lock() = 0;
		virtual void Unlock() = 0;

	protected:
		bool _locked;
	};
}