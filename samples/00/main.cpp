#include "uut.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	uut::SharedPtr<uut::Video> video(new uut::Video());
	video->SetMode(800, 600, false);
	auto window = video->GetWindow();
	auto input = window->GetInput();

	auto color = uut::Color(0.0f, 0.2f, 0.4f);

	uut::Camera camera;
	camera.InitProjMatrix(60, 800, 600, 0.1f, 1000.0f);

	uut::SharedPtr<uut::Geometry> geom(new uut::Geometry(video));
	geom->SetVertices({ uut::Vector3(0.00f, 0.5f, 0.0f), uut::Vector3(0.45f, -0.5f, 0.0f), uut::Vector3(-0.45f, -0.5f, 0.0f) });
	geom->SetColors({ uut::Color(1.0f, 0.0f, 0.0f, 1.0f), uut::Color(0.0f, 1.0f, 0.0f, 1.0f), uut::Color(0.0f, 0.0f, 1.0f, 1.0f) });
	geom->Generate();

	video->SetShader(geom->GetShader());

	while (video->MessagePool())
	{
		if (input->IsKey(uut::KEY_1))
			color = uut::Color::WHITE;
		if (input->IsKey(uut::KEY_2))
			color = uut::Color::BLACK;

		video->ClearTarget(color);
		geom->Draw();
		video->Present();
	}

	return 0;
}