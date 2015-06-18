#include "uutTexture.h"

namespace uut
{
	Texture::Texture()
		: _data(nullptr)
	{

	}

	Texture::~Texture()
	{
		if (_data)
			_data->Release();
	}

}