#include "uutRect.h"

namespace uut
{
	const Rectf Rectf::EMPTY(0, 0, 0, 0);

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
	const Recti Recti::EMPTY(0, 0, 0, 0);

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
