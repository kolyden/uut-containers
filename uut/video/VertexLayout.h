#pragma once
#include "VideoObject.h"
#include "containers/uutList.h"

namespace uut
{
	class VertexLayout : public VideoObject
	{
	public:
		VertexLayout(Video* video);
		virtual ~VertexLayout();

	protected:
		ID3D11InputLayout* _layout;
		List<VertexDeclare> _declare;

		friend class Video;
		friend class Shader;
	};
}