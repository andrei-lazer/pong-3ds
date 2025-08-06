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
			),
	leftScore(0), rightScore(0)
{
	ball.setVelocity(-1, 1);
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
		leftPaddle.setVelocity(0, -PongConstants::PADDLE_SPEED);
	}
	else if (kDown & KEY_DOWN)
	{
		leftPaddle.setVelocity(0, PongConstants::PADDLE_SPEED);
	}
	else
	{
		leftPaddle.setVelocity(0, 0);
	}

	// right paddle moves with XYAB
	if (kDown & KEY_X)
	{
		rightPaddle.setVelocity(0, -PongConstants::PADDLE_SPEED);
	}
	else if (kDown & KEY_B)
	{
		rightPaddle.setVelocity(0, PongConstants::PADDLE_SPEED);
	}
	else
	{
		rightPaddle.setVelocity(0, 0);
	}

	return false;
}

void Game::handleCollisions()
{
	// make ball bounce off the top and botton, and the paddles
	bool bounceOffTopBottom = ball.getY() <= 0 || ball.getY() >= TOP_SCREEN_HEIGHT - ball.h;
	if (bounceOffTopBottom)
	{
		ball.reflectY();
	}

	bool bounceOffLeft = (ball.getX() < leftPaddle.getX() + PongConstants::PADDLE_WIDTH) &&
		(ball.getY() > leftPaddle.getY()) && (ball.getY() < leftPaddle.getY() + PongConstants::PADDLE_HEIGHT);

	if (bounceOffLeft)
	{
		ball.reflectX();
	}

	bool bounceOffRight = (ball.getX() + PongConstants::BALL_SIZE > rightPaddle.getX()) &&
		(ball.getY() > rightPaddle.getY()) && (ball.getY() < rightPaddle.getY() + PongConstants::PADDLE_HEIGHT);

	if (bounceOffRight)
	{
		ball.reflectX();
	}

	// check if a score needs to be added to
	
	if (ball.getX() <= 0)
	{
		rightScore++;
		ball.reflectX();
	}
	else if (ball.getX() >= TOP_SCREEN_WIDTH - PongConstants::BALL_SIZE)
	{
		leftScore++;
		ball.reflectX();
	}
}

void Game::draw()
{
		renderer.initFrame();
		renderer.clearTopScreen();
		renderer.clearBottomScreen();

		renderer.drawRect(ball);
		renderer.drawRect(leftPaddle);
		renderer.drawRect(rightPaddle);

		// draw the score to the bottom screen
		renderer.drawScores(leftScore, rightScore);

		// never delete this - always needs to be at the end of the loop.
		C3D_FrameEnd(0);
}

void Game::update()
{
	leftPaddle.update();
	rightPaddle.update();
	ball.update();
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

		handleCollisions();
		update();
		draw();
	}
}

Game::~Game() {}
