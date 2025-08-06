#include "Game.hpp"
#include "common.hpp"

Game::Game()
	: renderer(),
	ball(
			PongConstants::BALL_SPAWN_X,
			PongConstants::BALL_SPAWN_Y,
			PongConstants::BALL_SIZE,
			PongConstants::BALL_SIZE
		),
	leftPaddle(
			PongConstants::LEFT_SPAWN_X,
			PongConstants::LEFT_SPAWN_Y,
			PongConstants::PADDLE_WIDTH,
			PongConstants::PADDLE_HEIGHT
			),
	rightPaddle(
			PongConstants::RIGHT_SPAWN_X,
			PongConstants::RIGHT_SPAWN_Y,
			PongConstants::PADDLE_WIDTH,
			PongConstants::PADDLE_HEIGHT
			)
{
	ball.setVelocityCartesian(1, 1);
}

bool Game::handleInputs()
{
	hidScanInput();
	kDown = hidKeysHeld();
	// return true if exiting
	if (kDown & KEY_START)
	{
		return true;
	}

	// then, check for inputs!
	
	// left paddle moves w dpad/circle pad
	if (kDown & KEY_UP)
	{
		leftPaddle.setVelocityCartesian(0, -PongConstants::PADDLE_SPEED);
	}
	else if (kDown & KEY_DOWN)
	{
		leftPaddle.setVelocityCartesian(0, PongConstants::PADDLE_SPEED);
	}
	else
	{
		leftPaddle.setVelocityCartesian(0, 0);
	}

	// right paddle moves with XYAB
	if (kDown & KEY_X)
	{
		rightPaddle.setVelocityCartesian(0, -PongConstants::PADDLE_SPEED);
	}
	else if (kDown & KEY_B)
	{
		rightPaddle.setVelocityCartesian(0, PongConstants::PADDLE_SPEED);
	}
	else
	{
		rightPaddle.setVelocityCartesian(0, 0);
	}

	return false;
}

void Game::draw()
{
		renderer.initFrame();
		renderer.clearTopScreen();
		renderer.clearBottomScreen();

		renderer.drawRect(ball);
		renderer.drawRect(leftPaddle);
		renderer.drawRect(rightPaddle);
		// never delete this - always needs to be at the end of the loop.
		C3D_FrameEnd(0);
}

void Game::update()
{
	leftPaddle.updatePos();
	rightPaddle.updatePos();
	ball.updatePos();
}

void Game::run()
{
	// variables for key and touch input
	while (aptMainLoop())
	{
		if(handleInputs())
		{
			break;
		}

		update();
		draw();
	}
}

Game::~Game() {}
