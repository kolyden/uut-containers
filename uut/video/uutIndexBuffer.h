#pragma once
#include "uutVideoBuffer.h"

namespace uut
{
	class UUT_API IndexBuffer : public VideoBuffer
	{
		OBJECT(IndexBuffer, VideoBuffer)
	public:
		IndexBuffer(Video* video);
	};
}