#pragma once
#include "uutTexture2D.h"

namespace uut
{
	class DepthTexture : public Texture2D
	{
		OBJECT(DepthTexture, Texture2D)
	public:
		DepthTexture(Video* video);
		virtual ~DepthTexture();

		void Clear();

	protected:
		ID3D11DepthStencilView* _view;

		friend class Video;
	};
}