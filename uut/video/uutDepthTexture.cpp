#include "uutDepthTexture.h"
#include "uutVideo.h"

namespace uut
{
	DepthTexture::DepthTexture(Video* video)
		: Texture2D(video)
		, _view(nullptr)
	{
	}

	DepthTexture::~DepthTexture()
	{
		if (_view)
			_view->Release();
	}

	void DepthTexture::Clear()
	{
		_video->GetContext()->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}