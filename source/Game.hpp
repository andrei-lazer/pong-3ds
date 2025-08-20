#pragma once

#include "Renderer.hpp"
#include "Rect.hpp"
#include "Button.hpp"
#include "CPUPlayer.hpp"

#include "citro2d.h"
#include <vector>
#include <memory>

enum class GameState
{
	PLAYING,
	PAUSE
};

class Game
{
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Paddle> leftPaddle;
	std::unique_ptr<Paddle> rightPaddle;
	std::unique_ptr<Button> unpauseButton;
	GameState state;
	bool isCPU;
	std::unique_ptr<CPU> cpu;

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

	bool handleInputs(u32 kDown, touchPosition touch);
	void handleGoalsScored();

	void pause();
public:
	Game();
	void run();
	~Game() = default;
};
