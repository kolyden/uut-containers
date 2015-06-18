#pragma once
#include "uutVideoObject.h"

namespace uut
{
	class RenderBuffer : public VideoObject
	{
	public:
		RenderBuffer(Video* video);
		virtual ~RenderBuffer();

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