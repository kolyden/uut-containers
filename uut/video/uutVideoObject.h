#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Video;

	class UUT_API VideoObject : public Object
	{
		OBJECT(VideoObject, Object)
	public:
		VideoObject(Video* video);
		virtual ~VideoObject() {}

	protected:
		WeakPtr<Video> _video;
	};
}