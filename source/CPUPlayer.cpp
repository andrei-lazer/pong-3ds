#include "CPUPlayer.hpp"

CPU::CPU(Paddle& paddle, Ball& ball) : paddle(paddle), ball(ball) {}

void CPU::controlPaddle()
{
	float targetDisplacement = ball.getY() - paddle.getY();

	// only updates velocity every 8 frames to allow for error
	static int frame = 0;
	frame ++;
	if (frame % 8 == 0)
	{
		if (targetDisplacement < PongConstants::BALL_SIZE)
		{
			paddle.moveUp();
		}
		else if (targetDisplacement > PongConstants::PADDLE_HEIGHT)
		{
			paddle.moveDown();
		}
		else
		{
			paddle.stop();
		}
	}
}
