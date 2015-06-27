#include "uutRect.h"

namespace uut
{
	Rectf::Rectf() {}

	Rectf::Rectf(float x, float y, float width, float height)
		: pos(x, y)
        , size(width, height)
	{
	}

	Rectf::Rectf(const Vector2f& _pos, const Vector2f& _size)
		: pos(_pos)
        , size(_size)
	{
	}

    //////////////////////////////////////////////////////////////////////////
    Recti::Recti() {}

    Recti::Recti(int x, int y, int width, int height)
        : pos(x, y)
        , size(width, height)
    {
    }

    Recti::Recti(const Vector2i& _pos, const Vector2i& _size)
        : pos(_pos)
        , size(_size)
    {
    }
}
