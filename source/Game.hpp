#pragma once

#include "Renderer.hpp"
#include "Rect.hpp"
#include "Button.hpp"
#include "CPUPlayer.hpp"
#include "common.hpp"

#include <memory>
#include <initializer_list>

enum class GameState
{
	PLAYING,
	PAUSE
};

class Game
{
	// large classes are kept in unique pointers to avoid memory leaks
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

	bool insideX(float x1, float w1, float x2, float w2);
	bool insideY(float x1, float w1, float x2, float w2);

	bool collidedX(Rect r1, Rect r2);
	bool collidedY(Rect r1, Rect r2);
	void handleCollisions();

	bool handleInputs(u32 kDown, touchPosition touch);

	void pause();
public:
	Game();
	void run();
	~Game() = default;
};
