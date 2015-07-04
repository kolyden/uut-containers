#include "uutVertexBuffer.h"

namespace uut
{
	VertexBuffer::VertexBuffer()
		: _data(NULL)
	{
	}

	VertexBuffer::~VertexBuffer()
	{
		if (_data)
			_data->Release();
	}

	void* VertexBuffer::Lock()
	{
		void* ptr;
		auto ret = _data->Lock(0, 0, &ptr, 0);
		if (ret != D3D_OK)
			return nullptr;

		_locked = true;
		return ptr;
	}

	void VertexBuffer::Unlock()
	{
		if (!_locked)
			return;

		_data->Unlock();
		_locked = false;
	}
}