#pragma once
#include "VideoObject.h"

namespace uut
{
	class BufferLayout : public VideoObject
	{
	public:
		BufferLayout(Video* video);
		virtual ~BufferLayout();

	protected:
		ID3D11InputLayout* _layout;

		friend class Video;
		friend class Shader;
	};
}