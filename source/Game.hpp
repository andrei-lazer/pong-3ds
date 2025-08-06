#pragma once

#include "Renderer.hpp"
#include "SolidRect.hpp"
#include "citro2d.h"

class Game
{
	Renderer renderer;
	Rect ball;
	Rect leftPaddle;
	Rect rightPaddle;
	u32 kDown;
	u32 kDownPrev;
private:
	void draw();
	void update();
	bool handleInputs();
	void moveBall();
	void handleCollisions();
public:
	Game();
	void run();
	~Game();
};
