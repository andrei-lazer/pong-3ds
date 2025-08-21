#pragma once

#include "Rect.hpp"
#include "common.hpp"

class CPU
{
public:
	CPU(Paddle& paddle, Ball& ball);
	void controlPaddle();
private:
	Paddle& paddle;
	Ball& ball;
};
