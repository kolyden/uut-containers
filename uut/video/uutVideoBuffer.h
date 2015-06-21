#pragma once
#include "uutVideoObject.h"

namespace uut
{
	class UUT_API VideoBuffer : public VideoObject
	{
		OBJECT(VideoBuffer, VideoObject)
	public:
		VideoBuffer(Video* video);
		virtual ~VideoBuffer();

		bool Update(const void* ptr, unsigned int size);
		void* Map();
		void Unmap();

		bool IsMapped() const { return _mapped; }

		ID3D11Buffer* GetData() const { return _data; }

	protected:
		ID3D11Buffer* _data;
		bool _mapped;

		friend class Video;
	};
}