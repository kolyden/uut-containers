#pragma once
#include "core/Object.h"
#include "VideoDefs.h"

namespace uut
{
	class Video;

	class VideoObject : public Object
	{
	public:
		VideoObject(Video* video);
		virtual ~VideoObject() {}

	protected:
		WeakPtr<Video> _video;
	};
}