#include "uutRenderTarget.h"
#include "uutVideo.h"

namespace uut
{
	RenderTarget::RenderTarget(Video* video)
		: Super(video)
		, _view(nullptr)
	{
	}

	RenderTarget::~RenderTarget()
	{
		if (_view)
			_view->Release();
	}

	void RenderTarget::Clear(const Color& color)
	{
		_video->GetContext()->ClearRenderTargetView(_view, color.m);
	}
}