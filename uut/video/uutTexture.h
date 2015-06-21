#pragma once
#include "uutVideoObject.h"

namespace uut
{
	class Texture : public VideoObject
	{
		OBJECT(Texture, VideoObject)
	public:
		Texture(Video* video);
		virtual ~Texture();

	protected:
		ID3D11Texture2D* _data;

		friend class Video;
	};
}