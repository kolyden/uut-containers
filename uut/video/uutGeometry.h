#pragma once
#include "uutVideoObject.h"
#include "uutColor.h"
#include "math/uutVector3.h"
#include "math/uutVector2.h"
#include "containers/uutList.h"

namespace uut
{
	class VertexBuffer;
	class Shader;

	class Geometry : public VideoObject
	{
	public:
		Geometry(Video* video);

		void SetVertices(const List<Vector3>& vertices);
		const List<Vector3>& GetVertices() const;

		void SetColors(const List<Color>& colors);
		const List<Color>& GetColors() const;

		void SetIndexes(const List<uint16_t>& indexes);
		const List<uint16_t>& GetIndexes() const;

		bool Generate();
		void Draw();

		Shader* GetShader() const { return _shader; }
		VertexBuffer* GetBuffer() const { return _vbuffer; }

	protected:
		List<Vector3> _vertices;
		List<Color> _colors;
		List<uint16_t> _indexes;
		SharedPtr<Shader> _shader;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<VertexBuffer> _ibuffer;
	};
}