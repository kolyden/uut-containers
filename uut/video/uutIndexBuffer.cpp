#include "uutIndexBuffer.h"

namespace uut
{
	IndexBuffer::IndexBuffer()
		: _data(NULL)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		if (_data != nullptr)
			_data->Release();
	}

	void* IndexBuffer::Lock(unsigned int offset, unsigned int size, bool discard)
	{
		void* ptr;
		auto ret = _data->Lock(offset, size, &ptr,
			(discard ? D3DLOCK_DISCARD : 0));
		if (ret != D3D_OK)
			return nullptr;

		_locked = true;
		return ptr;
	}

	void IndexBuffer::Unlock()
	{
		if (!_locked)
			return;

		_data->Unlock();
		_locked = false;
	}

	bool IndexBuffer::Update(const void* data, unsigned int offset, unsigned int size)
	{
		void* ptr;
		auto ret = _data->Lock(offset, size, &ptr, D3DLOCK_DISCARD);
		if (ret != D3D_OK)
			return false;

		memcpy(ptr, data, size);
		return true;
	}
}