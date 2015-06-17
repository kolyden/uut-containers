#pragma once
#include "VideoObject.h"

namespace uut
{
	class BufferLayout;

	class Shader : public VideoObject
	{
	public:
		Shader(Video* video);
		virtual ~Shader();

		void Clear();
		bool IsEmpty() const;

		SharedPtr<BufferLayout> CreateLayout(D3D11_INPUT_ELEMENT_DESC* desc, BYTE count);

	protected:
		ID3D10Blob* _vsBlob;
		ID3D10Blob* _psBlob;
		ID3D11VertexShader* _vs;
		ID3D11PixelShader* _ps;

		friend class Video;
	};
}