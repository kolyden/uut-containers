#pragma once
#include "uutVideoObject.h"
#include "containers/uutList.h"

namespace uut
{
	class VertexLayout;

	class Shader : public VideoObject
	{
	public:
		Shader(Video* video);
		virtual ~Shader();

		void Clear();
		bool IsEmpty() const;

	protected:
		ID3D10Blob* _vsBlob;
		ID3D10Blob* _psBlob;
		ID3D11VertexShader* _vs;
		ID3D11PixelShader* _ps;
		ID3D11InputLayout* _layout;
		List<VertexDeclare> _declare;

		friend class Video;
	};
}