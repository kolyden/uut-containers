#pragma once
#include "VideoObject.h"

namespace uut
{
	class VideoBuffer : public VideoObject
	{
	public:
		VideoBuffer(Video* video);
		virtual ~VideoBuffer();

		bool Update(const void* ptr, unsigned int size);
		void* Map();
		void Unmap();

		bool IsMapped() const { return _mapped; }

	protected:
		ID3D11Buffer* _data;
		bool _mapped;

		friend class Video;
	};
}