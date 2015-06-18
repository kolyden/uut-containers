#pragma once
#include "core/uutDefs.h"

namespace uut
{
	class Color
	{
	public:
		union
		{
			float m[4];
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
		};

		Color();
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);

		static const Color BLACK;
		static const Color WHITE;
	};
}