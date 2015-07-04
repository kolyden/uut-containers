#pragma once
#include "core/uutDefs.h"

namespace uut
{
	class Color4f
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

		Color4f();
		Color4f(float r, float g, float b);
		Color4f(float r, float g, float b, float a);

		static const Color4f BLACK;
		static const Color4f WHITE;
	};

	//////////////////////////////////////////////////////////////////////////
	class Color4b
	{
	public:
		union
		{
			uint32_t data;
			struct
			{
				uint8_t b;
				uint8_t g;
				uint8_t r;
				uint8_t a;
			};
		};

		Color4b() {}
		explicit Color4b(uint32_t color) : data(color) {}
		Color4b(uint8_t _r, uint8_t _g, uint8_t _b)
			: r(_r), g(_g), b(_b), a(255) {}
		Color4b(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
			: r(_r), g(_g), b(_b), a(_a) {}

		static const Color4b BLACK;
		static const Color4b WHITE;
		static const Color4b RED;
		static const Color4b GREEN;
		static const Color4b BLUE;
	};
}