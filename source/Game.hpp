#pragma once

#include "Renderer.hpp"
#include "Rect.hpp"
#include "citro2d.h"
#include <vector>
#include "Button.hpp"

enum class GameState
{
	PLAYING,
	PAUSE
};

class Game
{
	Renderer renderer;
	Ball ball;
	Rect leftPaddle;
	Rect rightPaddle;
	Button unpauseButton;
	GameState state;

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

	void pause();
public:
	Game();
	void run();
	~Game();
};
