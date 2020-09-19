#include "Sketch.hh"

Sketch::Sketch()
{
	InitWindow(screenWidth, screenHeight, windowName.c_str());
	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
}

void Sketch::resetWindow()
{
	CloseWindow(); // Close window and OpenGL context
	InitWindow(screenWidth, screenHeight, windowName.c_str());
	SetTargetFPS(fps); // Set our game to run at 60 frames-per-second
};

Sketch::operator int()
{
	MainLoop();
	return 0;
};

auto Sketch::MainLoop() -> void
{
	this->Setup();
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		this->Update();

		BeginDrawing();

		this->Draw();

		EndDrawing();
	}
	this->Unload();
}

Sketch::~Sketch()
{
	CloseWindow(); // Close window and OpenGL context
}