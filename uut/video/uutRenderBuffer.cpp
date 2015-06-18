#include "uutRenderBuffer.h"
#include "uutVideo.h"

namespace uut
{
	RenderBuffer::RenderBuffer(Video* video)
		: VideoObject(video)
		, _data(nullptr)
		, _mapped(false)
	{
	}

	RenderBuffer::~RenderBuffer()
	{
		if (_data)
			_data->Release();
	}

	bool RenderBuffer::Update(const void* ptr, unsigned int size)
	{
		if (_data == nullptr)
			return false;

		D3D11_MAPPED_SUBRESOURCE ms;
		const int ret = _video->GetContext()->Map(_data, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		if (ret != S_OK)
			return false;

		memcpy(ms.pData, ptr, size);
		_video->GetContext()->Unmap(_data, NULL);

		return true;
	}

	void* RenderBuffer::Map()
	{
		if (_data == nullptr)
			return nullptr;

		D3D11_MAPPED_SUBRESOURCE ms;
		const int ret = _video->GetContext()->Map(_data, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		if (ret != S_OK)
			return nullptr;

		_mapped = true;
		return ms.pData;
	}

	void RenderBuffer::Unmap()
	{
		if (!_mapped)
			return;

		_video->GetContext()->Unmap(_data, NULL);
		_mapped = false;
	}
}