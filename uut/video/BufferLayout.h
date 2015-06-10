#pragma once
#include "VideoDefs.h"

namespace uut
{
	class BufferLayout
	{
	public:
		BufferLayout();
		virtual ~BufferLayout();

	protected:
		ID3D11InputLayout* _layout;

		friend class Video;
	};
}