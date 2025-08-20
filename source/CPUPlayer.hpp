#pragma once

#include "Rect.hpp"

class CPU
{
public:
	CPU(Paddle& paddle, Ball& ball);
	void controlPaddle();
private:
	Paddle& paddle;
	Ball& ball;
	float expectedY(float paddleX, float ballX, float ballY, float ballVX, float ballVY);
};
