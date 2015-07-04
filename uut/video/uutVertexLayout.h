#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"
#include "containers/uutList.h"

namespace uut
{
	class VertexLayout : public Object
	{
		OBJECT(VertexLayout, Object)
	public:
		VertexLayout();
		virtual ~VertexLayout();

	protected:
		LPDIRECT3DVERTEXDECLARATION9 _data;
		List<VertexDeclare> _declare;

		friend class Render;
	};
}