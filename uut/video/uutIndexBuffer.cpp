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

	void* IndexBuffer::Lock()
	{
		void* ptr;
		auto ret = _data->Lock(0, 0, &ptr, 0);
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
}