#pragma once
#include "VideoDefs.h"

namespace uut
{
	class Color32
	{
	public:
		union
		{
			uint32_t data;
			struct
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
		};

		Color32() {}
		explicit Color32(uint32_t color) : data(color) {}
		Color32(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
			: r(_r), g(_g), b(_b), a(_a) {}

		static const Color32 BLACK;
		static const Color32 WHITE;
	};
}