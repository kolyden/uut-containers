#include "uutMatrix.h"

namespace uut
{
	Matrix4::Matrix4() {}

	Matrix4::Matrix4(const float* mat)
	{
		memcpy(m, mat, sizeof(float) * 16);
	}

	Matrix4 Matrix4::buildOrtho(const Rectf& rect,
		float znear, float zfar)
	{
		Matrix4 ret;

        const float left = rect.pos.x;
        const float right = left + rect.size.x;

        const float top = rect.pos.y;
        const float bottom = top + rect.size.y;

        const float r_l = (right - left);
		const float t_b = (top - bottom);
		const float f_n = (zfar - znear);

		const float tx = -(right + left) / r_l;
		const float ty = -(top + bottom) / t_b;
		const float tz = -(zfar + znear) / f_n;

		ret.m[0][0] = 2.0f / r_l;
		ret.m[0][1] = 0.0f;
		ret.m[0][2] = 0.0f;
		ret.m[0][3] = 0.0f;

		ret.m[1][0] = 0.0f;
		ret.m[1][1] = 2.0f / t_b;
		ret.m[1][2] = 0.0f;
		ret.m[1][3] = 0.0f;

		ret.m[2][0] = 0.0f;
		ret.m[2][1] = 0.0f;
		ret.m[2][2] = -2.0f / f_n;
		ret.m[2][3] = 0.0f;

		ret.m[3][0] = tx;
		ret.m[3][1] = ty;
		ret.m[3][2] = tz;
		ret.m[3][3] = 1.0f;

		return ret;
	}
}
