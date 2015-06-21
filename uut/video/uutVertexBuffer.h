#pragma once
#include "uutVideoBuffer.h"

namespace uut
{
	class UUT_API VertexBuffer : public VideoBuffer
	{
		OBJECT(VertexBuffer, VideoBuffer)
	public:
		VertexBuffer(Video* video);
	};
}