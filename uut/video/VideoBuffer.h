#pragma once
#include "VideoDefs.h"

namespace uut
{
	class VideoBuffer
	{
	public:
		VideoBuffer();
		virtual ~VideoBuffer();

	protected:
		ID3D11Buffer* _data;

		friend class Video;
	};
}