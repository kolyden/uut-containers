#pragma once
#include "uutVideoObject.h"
#include "uutColor.h"
#include "math/uutVector3.h"
#include "math/uutVector2.h"
#include "containers/uutList.h"

namespace uut
{
	class RenderBuffer;
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
		void Draw();

		Shader* GetShader() const { return _shader; }
		RenderBuffer* GetBuffer() const { return _buffer; }

	protected:
		List<Vector3> _vertices;
		List<Color> _colors;
		SharedPtr<Shader> _shader;
		SharedPtr<RenderBuffer> _buffer;
	};
}