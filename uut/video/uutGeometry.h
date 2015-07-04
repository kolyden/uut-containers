#pragma once
#include "core/uutObject.h"
#include "math/uutColor.h"
#include "math/uutVector3.h"
#include "math/uutVector2.h"
#include "math/uutVertex.h"
#include "containers/uutList.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Render;
	class VertexBuffer;
	class IndexBuffer;
	class VertexLayout;

	class Geometry : public Object
	{
		OBJECT(Geometry, Object)
	public:
		Geometry(Render* render, int vertexCount = 2048, int indexCount = 4096);

		void SetPrimitive(EPrimitiveType type);
		EPrimitiveType GetPrimitive() const;

		void SetVertices(const List<Vector3f>& vertices);
		const List<Vector3f>& GetVertices() const;

		void SetColors(const List<Color4b>& colors);
		const List<Color4b>& GetColors() const;

		void SetUV(const List<Vector2f>& uvs);
		const List<Vector2f>& GetUV() const;

		void SetIndexes(const List<uint16_t>& indexes);
		const List<uint16_t>& GetIndexes() const;

		bool Generate();
		void Clear();
		void Draw();

	protected:
		WeakPtr<Render> _render;
		List<Vector3f> _vertices;
		List<Color4b> _colors;
		List<Vector2f> _uvs;
		List<uint16_t> _indexes;
		EPrimitiveType _type;
		int _vertexCount;
		int _indexCount;

		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<IndexBuffer> _ibuffer;
		SharedPtr<VertexLayout> _layout;
	};
}