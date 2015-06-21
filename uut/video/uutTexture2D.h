#pragma once
#include "uutTexture.h"

namespace uut
{
	class Texture2D : public Texture
	{
		OBJECT(Texture2D, Texture)
	public:
		Texture2D(Video* video);
	};
}