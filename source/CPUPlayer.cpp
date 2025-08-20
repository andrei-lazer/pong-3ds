#include "CPUPlayer.hpp"
#include "common.hpp"

CPU::CPU(Paddle& paddle, Ball& ball) : paddle(paddle), ball(ball)
{}

float CPU::expectedY(float paddleX, float ballX, float ballY, float ballVX, float ballVY)
{
	float timeToHit;
	if (ballVX > 0)
	{
		timeToHit = (paddleX - ballX) / ballVX;
	}
	else
	{
		timeToHit = (paddleX + ballX) / -ballVX;
	}
	if (timeToHit < 0)
	{
		paddle.setPosition(0, 0);
	}
	float overallY = ballY + ballVY*timeToHit;
	// use bounces to predict where the ball will hit
	int numberOfBounce = (int)overallY / TOP_SCREEN_HEIGHT;
	float bouncedY;
	if (numberOfBounce % 2 == 0)
	{
		bouncedY = overallY - numberOfBounce*TOP_SCREEN_HEIGHT;
	}
	else
	{
		bouncedY = (numberOfBounce+1)*TOP_SCREEN_HEIGHT - overallY;
	}
	return bouncedY;
	
}

void CPU::controlPaddle()
{
	static int frame = 0;
	// guess where the ball ends up - only works for right side right now
	float targetY = expectedY(paddle.getX(), ball.getX(), ball.getY(), ball.getVX(), ball.getVY());

	// check displacement every 10 frames
	float targetDisplacement = targetY - paddle.getY();
	frame ++;

	if (frame % 1 == 0)
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
