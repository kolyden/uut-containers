#include "Shader.h"
#include <D3DX11.h>

namespace uut
{
	Shader::Shader()
		: _blob(nullptr)
		, _vs(nullptr)
		, _ps(nullptr)
	{
	}

	Shader::~Shader()
	{
		if (_vs)
			_vs->Release();
		if (_ps)
			_ps->Release();
		if (_blob)
			_blob->Release();
	}

	void Shader::Clear()
	{
		if (IsEmpty())
			return;

		if (_vs)
		{
			_vs->Release();
			_vs = nullptr;
		}
		if (_ps)
		{
			_ps->Release();
			_ps = nullptr;
		}
		if (_blob)
		{
			_blob->Release();
			_blob = nullptr;
		}
	}

	bool Shader::IsEmpty() const
	{
		return _vs == nullptr && _ps == nullptr;
	}

}