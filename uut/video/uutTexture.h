#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"
#include "math/uutVector2.h"

namespace uut
{
	class Texture : public Object
	{
		OBJECT(Texture, Object)
	public:
		Texture();
		virtual ~Texture();

		const Vector2i& GetSize() const { return _size; }

	protected:
		LPDIRECT3DTEXTURE9 _data;
		Vector2i _size;

		friend class Render;
	};
}