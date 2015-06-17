#include "Shader.h"
#include "Video.h"
#include "BufferLayout.h"

namespace uut
{
	static const char* g_shader =
		"struct VOut \
		{ \
			float4 position : SV_POSITION; \
			float4 color : COLOR; \
		}; \
		VOut VShader(float4 position : POSITION, float4 color : COLOR) \
		{ \
			VOut output; \
			output.position = position; \
			output.color = color; \
			return output; \
		} \
		float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET \
		{ \
			return color; \
		}";

	Shader::Shader(Video* video)
		: VideoObject(video)
		, _vsBlob(nullptr)
		, _psBlob(nullptr)
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
		if (_vsBlob)
			_vsBlob->Release();
		if (_psBlob)
			_psBlob->Release();
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
		if (_vsBlob)
		{
			_vsBlob->Release();
			_vsBlob = nullptr;
		}
		if (_psBlob)
		{
			_psBlob->Release();
			_psBlob = nullptr;
		}
	}

	bool Shader::IsEmpty() const
	{
		return _vs == nullptr && _ps == nullptr;
	}

	SharedPtr<BufferLayout> Shader::CreateLayout(D3D11_INPUT_ELEMENT_DESC* desc, BYTE count)
	{
		if (_vsBlob == nullptr || desc == nullptr)
			return SharedPtr<BufferLayout>::EMPTY;

		SharedPtr<BufferLayout> layout(new BufferLayout(_video));
		auto ptr = _vsBlob->GetBufferPointer();
		auto size = _vsBlob->GetBufferSize();
		auto ret = _video->GetDevice()->CreateInputLayout(desc, count, ptr, size, &layout->_layout);
		if (ret != S_OK)
			return SharedPtr<BufferLayout>::EMPTY;

		return layout;
	}
}