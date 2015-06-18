#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"

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