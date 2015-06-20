#include "video/uutVideo.h"
#include "video/uutShader.h"
#include "video/uutRenderBuffer.h"
#include "video/uutColor.h"
#include "math/uutVector3.h"
#include "video/uutGeometry.h"

static const char* g_shader =
	"struct VOut \
	{ \
		float4 position : SV_POSITION; \
		float4 color : COLOR; \
	}; \
	VOut VShader(float4 position : POSITION, float4 color : COLOR) \
	{ \
		VOut output; \
		output.position = position; \
		output.color = color; \
		return output; \
	} \
	float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET \
	{ \
		return color; \
	}";

struct MyVertex
{
	uut::Vector3 pos;
	uut::Color color;
};

uut::VertexDeclare g_decl[] =
{
	{ 0, uut::VertexUsage::Position, uut::VertexType::Float, 3, 0 },
	{ 0, uut::VertexUsage::Color, uut::VertexType::Float, 4, sizeof(float)* 3 },
};

static const MyVertex g_verts[] =
{
	{ uut::Vector3(0.00f, 0.5f, 0.0f), uut::Color(1.0f, 0.0f, 0.0f, 1.0f) },
	{ uut::Vector3(0.45f, -0.5f, 0.0f), uut::Color(0.0f, 1.0f, 0.0f, 1.0f) },
	{ uut::Vector3(-0.45f, -0.5f, 0.0f), uut::Color(0.0f, 0.0f, 1.0f, 1.0f) },
};

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	uut::SharedPtr<uut::Video> video(new uut::Video());
	video->SetMode(800, 600, false);

	auto color = uut::Color(0.0f, 0.2f, 0.4f);

// 	auto shader = video->CreateShaderFromMemory(g_decl, 2, g_shader);
// 	video->SetShader(shader);

// 	auto buf = video->CreateBuffer(sizeof(MyVertex)* 3);
// 	buf->Update(g_verts, sizeof(MyVertex)* 3);

	uut::SharedPtr<uut::Geometry> geom(new uut::Geometry(video));
	geom->SetVertices({ uut::Vector3(0.00f, 0.5f, 0.0f), uut::Vector3(0.45f, -0.5f, 0.0f), uut::Vector3(-0.45f, -0.5f, 0.0f) });
	geom->SetColors({ uut::Color(1.0f, 0.0f, 0.0f, 1.0f), uut::Color(0.0f, 1.0f, 0.0f, 1.0f), uut::Color(0.0f, 0.0f, 1.0f, 1.0f) });
	geom->Generate();

	video->SetShader(geom->GetShader());

	while (video->MessagePool())
	{
		video->ClearTarget(color);
		geom->Draw();
// 		video->SetBuffer(buf, sizeof(MyVertex), 0);
// 		video->SetTopology(uut::VertexTopology::TriangleList);
// 		video->Draw(3, 0);

		video->Present();
	}

	return 0;
}