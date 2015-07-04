#pragma once
#include "uutVector2.h"

namespace uut
{
	class Rectf
	{
	public:
		Vector2f pos;
		Vector2f size;

		Rectf();
		Rectf(float x, float y, float width, float height);
		Rectf(const Vector2f& pos, const Vector2f& size);

		static const Rectf EMPTY;
	};

	//////////////////////////////////////////////////////////////////////////
    class Recti
    {
    public:
        Vector2i pos;
        Vector2i size;

        Recti();
        Recti(int x, int y, int width, int height);
        Recti(const Vector2i& pos, const Vector2i& size);

		static const Recti EMPTY;
    };
}
