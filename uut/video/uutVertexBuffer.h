#pragma once
#include "uutVideoObject.h"

namespace uut
{
	class VertexBuffer : public VideoObject
	{
	public:
		VertexBuffer(Video* video);
		virtual ~VertexBuffer();

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