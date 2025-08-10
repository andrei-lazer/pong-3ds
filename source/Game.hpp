#pragma once

#include "Renderer.hpp"
#include "Rect.hpp"
#include "citro2d.h"
#include <vector>
#include "Button.hpp"

class Game
{
	Renderer renderer;
	Rect ball;
	Rect leftPaddle;
	Rect rightPaddle;
	std::vector<Button> buttons;

	u32 kDown;
	u32 kDownPrev;
	int leftPoints;
	int rightPoints;
private:
	void draw();
	void update();
	void moveBall();


	bool insideX(float x1, float w1, float x2, float w2);
	bool insideY(float x1, float w1, float x2, float w2);

	bool collidedX(Rect r1, Rect r2);
	bool collidedY(Rect r1, Rect r2);
	void handlePaddleCollisions();
	void handleWallCollisions();
	void handleCollisions();

	bool handleInputs();
	void handleGoalsScored();

	void pointScoredPause();
public:
	Game();
	void run();
	~Game();
};
