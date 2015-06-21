#include "uutVideoBuffer.h"
#include "uutVideo.h"

namespace uut
{
	VideoBuffer::VideoBuffer(BufferType type, Video* video)
		: Super(video)
		, _type(type)
		, _data(nullptr)
		, _mapped(false)
	{
	}

	VideoBuffer::~VideoBuffer()
	{
		if (_data != nullptr)
			_data->Release();
	}

	bool VideoBuffer::Update(const void* ptr, unsigned int size)
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

	void* VideoBuffer::Map()
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

	void VideoBuffer::Unmap()
	{
		if (!_mapped)
			return;

		_video->GetContext()->Unmap(_data, NULL);
		_mapped = false;
	}
}