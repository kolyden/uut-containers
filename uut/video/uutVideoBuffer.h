#pragma once
#include "uutVideoObject.h"

namespace uut
{
	class UUT_API VideoBuffer : public VideoObject
	{
		OBJECT(VideoBuffer, VideoObject)
	public:
		VideoBuffer(BufferType type, Video* video);
		virtual ~VideoBuffer();

		bool Update(const void* ptr, unsigned int size);
		void* Map();
		void Unmap();

		bool IsMapped() const { return _mapped; }

		ID3D11Buffer* GetData() const { return _data; }
		BufferType GetType() const { return _type; }

	protected:
		ID3D11Buffer* _data;
		bool _mapped;

	private:
		BufferType _type;

		friend class Video;
	};
}