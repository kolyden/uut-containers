#pragma once
#include "VideoDefs.h"

namespace uut
{

	class Shader
	{
	public:
		Shader();
		virtual ~Shader();

		void Clear();
		bool IsEmpty() const;

	protected:
		ShaderType _type;
		ID3D10Blob* _blob;
		ID3D11VertexShader* _vs;
		ID3D11PixelShader* _ps;

		friend class Video;
	};
}