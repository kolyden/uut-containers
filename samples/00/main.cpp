#include "video/Video.h"
#include "video/Shader.h"
#include "video/VideoBuffer.h"
#include "video/BufferLayout.h"
#include "video/Color.h"

struct VERTEX
{
	FLOAT x, y, z;      // position
	float color[4];    // color
};

D3D11_INPUT_ELEMENT_DESC ied[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const VERTEX g_verts[] =
{
	{ 0.0f, 0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
	{ 0.45f, -0.5, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
	{ -0.45f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f } }
};

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	auto video = std::make_shared<uut::Video>();
	video->SetMode(800, 600, false);

	auto color = uut::Color(0.0f, 0.2f, 0.4f);

	auto shader = video->CreateShaderFromFile(L"Data/Shaders/simple.shader");
	video->SetShader(shader);

	auto layout = shader->CreateLayout(ied, 2);
	video->SetLayout(layout);

	auto buf = video->CreateBuffer(sizeof(VERTEX)* 3);
	buf->Update(g_verts, sizeof(VERTEX)* 3);

	while (video->MessagePool())
	{
		video->ClearTarget(color);
		video->SetBuffer(buf, sizeof(VERTEX), 0);
		video->SetTopology(uut::VertexTopology::TriangleList);
		video->Draw(3, 0);

		video->Present();
	}

	return 0;
}