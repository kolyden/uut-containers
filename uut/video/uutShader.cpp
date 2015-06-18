#include "uutShader.h"
#include "uutVideo.h"

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
		, _layout(0)
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
/*
	static DXGI_FORMAT SelectFormat(VertexType type, uint8_t count)
	{
		switch (type)
		{
		case uut::VertexType::SByte:
			break;

		case uut::VertexType::UByte:
			break;

		case uut::VertexType::SShort:
			break;

		case uut::VertexType::UShort:
			break;

		case uut::VertexType::Float:
			switch (count)
			{
			case 3:return DXGI_FORMAT_R32G32B32_FLOAT;
			case 4:return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			break;
		}

		return DXGI_FORMAT_UNKNOWN;
	}
	
	SharedPtr<VertexLayout> Shader::CreateLayout(const VertexDeclare* decl, uint8_t count)
	{
		static const char* semanticName[3] = { "POSITION", "TEXCOORDS", "COLOR" };

		if (_vsBlob == nullptr || count == 0)
			return SharedPtr<VertexLayout>::EMPTY;

		SharedPtr<VertexLayout> layout(new VertexLayout(_video));
		layout->_declare = List<VertexDeclare>(decl, count);

		List<D3D11_INPUT_ELEMENT_DESC> desc;
		desc.SetSize(count);

		for (int i = 0; i < count; i++)
		{
			desc[i].SemanticName = semanticName[(int)decl[i]._usage];
			desc[i].SemanticIndex = 0;
			desc[i].Format = SelectFormat(decl[i]._type, decl[i]._count);
			desc[i].InputSlot = 0;
			desc[i].AlignedByteOffset = decl[i]._offset;
			desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc[i].InstanceDataStepRate = 0;
		}

		auto ptr = _vsBlob->GetBufferPointer();
		auto size = _vsBlob->GetBufferSize();
		auto ret = _video->GetDevice()->CreateInputLayout(desc.GetData(), count, ptr, size, &layout->_layout);
		if (ret != S_OK)
			return SharedPtr<VertexLayout>::EMPTY;

		return layout;
	}*/
}