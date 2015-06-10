#pragma once
#include "core/Defs.h"
#include <d3d11.h>
\
namespace uut
{
	class Texture
	{
	public:
		Texture();
		virtual ~Texture();

	protected:
		ID3D11Texture2D* _data;

		friend class Video;
	};
}