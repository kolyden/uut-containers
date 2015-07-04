#include "uutVertex.h"

namespace uut
{
	const List<VertexDeclare> Vertex::DECLARE = {
		{ DECLARE_POSITION, VALUE_FLOAT, 3, 0 },
		{ DECLARE_COLOR, VALUE_DWORD, 1, offsetof(Vertex, color) },
		{ DECLARE_TEXCOORDS, VALUE_FLOAT, 2, offsetof(Vertex, tex) },
	};
}