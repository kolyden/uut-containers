#pragma once
#include "uutTexture2D.h"
#include "uutColor.h"

namespace uut
{
	class RenderTarget : public Texture2D
	{
		OBJECT(RenderTarget, Texture2D)
	public:
		RenderTarget(Video* video);
		virtual ~RenderTarget();

		void Clear(const Color& color);

	protected:
		ID3D11RenderTargetView* _view;

		friend class Video;
	};
}