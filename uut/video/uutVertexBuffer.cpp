#include "uutVertexBuffer.h"
#include "uutVideo.h"

namespace uut
{
	VertexBuffer::VertexBuffer(Video* video)
		: Super(BufferType::Vertex, video)
	{
	}
}