#pragma once
#include "VideoObject.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

namespace uut
{
	class VertexBuffer;
	class VertexLayout;
	class Shader;

	class Geometry : public VideoObject
	{
	public:
		Geometry(Video* video);

		void SetVertices(const List<Vector3>& vertices);
		const List<Vector3>& GetVertices() const;

		void SetColors(const List<Color>& colors);
		const List<Color>& GetColors() const;

		bool Generate();
		SharedPtr<VertexBuffer> GetBuffer() { return _buffer; }

	protected:
		List<Vector3> _vertices;
		List<Color> _colors;
		SharedPtr<Shader> _vshader;
		SharedPtr<Shader> _pshader;
		SharedPtr<VertexBuffer> _buffer;
		SharedPtr<VertexLayout> _layout;
	};
}