#include "video/Video.h"
#include "video/Shader.h"
#include "video/VideoBuffer.h"
#include "video/BufferLayout.h"

static const char* g_shader = 
	"struct VOut"
	"{"
	"	float4 position : SV_POSITION;"
	"	float4 color : COLOR;"
	"};"
	"VOut VShader(float4 position : POSITION, float4 color : COLOR)"
	"{"
	"	VOut output;"
	"	output.position = position;"
	"	output.color = color;"
	"	return output;"
	"}"
	"float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET"
	"{"
	"	return color;"
	"}";

struct VERTEX
{
	FLOAT X, Y, Z;      // position
	D3DXCOLOR Color;    // color
};

D3D11_INPUT_ELEMENT_DESC ied[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const VERTEX g_verts[] =
{
	{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
	{ 0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
	{ -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
};

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	auto video = uut::Video();
	video.SetMode(800, 600, false);

	auto color = uut::Color(0.0f, 0.2f, 0.4f);

	auto vs = video.CreateShaderFromFile("shaders.shader", uut::ShaderType::Vertex);
	auto ps = video.CreateShaderFromFile("shaders.shader", uut::ShaderType::Pixel);
	video.SetShader(uut::ShaderType::Vertex, vs);
	video.SetShader(uut::ShaderType::Pixel, ps);

	auto layout = video.CreateLayout(ied, 2, vs);
	video.SetLayout(layout);

	auto buf = video.CreateBuffer(sizeof(VERTEX)* 3);
	video.UpdateBuffer(buf, g_verts, sizeof(VERTEX)* 3);

	while (video.MessagePool())
	{
		video.ClearTarget(color);
		video.SetBuffer(buf, sizeof(VERTEX), 0);
		video.SetTopology(uut::VertexTopology::TriangleList);
		video.Draw(3, 0);
		video.Present();
	}

	return 0;
}