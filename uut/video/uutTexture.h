#pragma once
#include "core/uutObject.h"
#include "uutVideoDefs.h"
#include "math/uutVector2.h"

namespace uut
{
	struct TextureRect
	{
		void* _bits;
		unsigned _pitch;

		TextureRect() {}
		TextureRect(void* bits, unsigned pitch)
			: _bits(bits), _pitch(pitch)
		{}

		static const TextureRect EMPTY;
	};

	class Texture : public Object
	{
	public:
		Texture();
		virtual ~Texture();

		const Vector2i& GetSize() const { return _size; }

		TextureRect Lock();
		void Unlock();

	protected:
		LPDIRECT3DTEXTURE9 _data;
		Vector2i _size;

		friend class Render;
	};
}