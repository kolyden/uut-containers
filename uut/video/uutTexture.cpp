#include "uutTexture.h"

namespace uut
{
	Texture::Texture(Video* video)
		: VideoObject(video)
		, _data(nullptr)
	{

	}

	Texture::~Texture()
	{
		if (_data)
			_data->Release();
	}
}