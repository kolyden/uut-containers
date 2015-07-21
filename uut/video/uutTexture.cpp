#include "uutTexture.h"

namespace uut
{
	const TextureRect TextureRect::EMPTY(NULL, 0);

	Texture::Texture()
		: _data(NULL)
		, _size(0)
	{
	}

	Texture::~Texture()
	{
		if (_data != nullptr)
			_data->Release();
	}

	TextureRect Texture::Lock()
	{
		D3DLOCKED_RECT rect;
		if (_data->LockRect(0, &rect, NULL, 0) != D3D_OK)
			return TextureRect::EMPTY;

		return TextureRect(rect.pBits, rect.Pitch);
	}

	void Texture::Unlock()
	{
		_data->UnlockRect(0);
	}
}