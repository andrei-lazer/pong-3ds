#include "Game.hpp"
#include "common.hpp"
#include <cmath>

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
	buttons(),
	leftPoints(0), rightPoints(0)
{
	ball.setVelocity(-PongConstants::BALL_SPEED, 1);
	ball.setVelocityPolar(PongConstants::BALL_SPEED, PI/3);
	// adding buttons
	Button nextPoint = Button(
			100, 100,
			200, 100,
			"Go",
			testFunc,
			Renderer::BOTTOM,
			red,
			green,
			10);
	/* buttons.push_back(nextPoint); */
}

void Game::pointScoredPause()
{
	// respawn the ball in the middle of the screen
	ball.setPosition(PongConstants::BALL_SPAWN_X, PongConstants::BALL_SPAWN_Y);
	// show a button on the bottom screen
	//
	// start ball with random direction
	float randomAngle = randomFloat(-PI/4, PI/4);
	ball.setVelocityPolar(PongConstants::BALL_SPEED, randomAngle);
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

bool Game::insideX(float x1, float w1, float x2, float w2)
{
	return (x1 + w1 >= x2) && (x2 + w2 >= x1);
}

bool Game::insideY(float y1, float w1, float y2, float w2)
{
	return (y1 + w1 >= y2) && (y2 + w2 >= y1);
}

void Game::handlePaddleCollisions()
{
	std::vector<Rect> paddles = {leftPaddle, rightPaddle};
	for (auto p : paddles)
	{
		// collided horizontally
		float paddlePrevX = p.getX() - p.getVX();
		float ballPrevX = ball.getX() - ball.getVX();
		if (!insideX(paddlePrevX, p.w, ballPrevX, ball.w)
				&& insideY(p.getY(), p.h, ball.getY(), ball.h)
				&& insideX(p.getX(), p.w, ball.getX(), ball.w))
		{
			ball.reflectX();
			ball.setVelocity(ball.getVX(), ball.getVY() + p.getVY()*PongConstants::BALL_SPIN_FACTOR);
		}

		float paddlePrevY = p.getY() - p.getVY();
		float ballPrevY = ball.getY() - ball.getVY();
		if (!insideY(paddlePrevY, p.h, ballPrevY, ball.h)
				&& insideY(p.getY(), p.h, ball.getY(), ball.h)
				&& insideX(p.getX(), p.w, ball.getX(), ball.w))
		{
			ball.reflectY();
			ball.setVelocity(ball.getVX() + p.getVX()*PongConstants::BALL_SPIN_FACTOR, ball.getVY());
		}
	}
}

void Game::handleCollisions()
{
	handlePaddleCollisions();

	// make ball bounce off the top and botton, and the paddles
	bool bounceOffTopBottom = ball.getY() <= 0 || ball.getY() >= TOP_SCREEN_HEIGHT - ball.h;
	if (bounceOffTopBottom)
	{
		ball.reflectY();
	}


	// check if a score needs to be changed
	if (ball.getX() <= 0)
	{
		/* rightScores(); */
		rightPoints++;
		pointScoredPause();
	}
	else if (ball.getX() >= TOP_SCREEN_WIDTH - PongConstants::BALL_SIZE)
	{
		leftPoints++;
		pointScoredPause();
	}

	// make sure paddles don't go off screen
	if ((leftPaddle.getY() <= 0 && leftPaddle.getVY() < 0) ||
			(leftPaddle.getY() >= TOP_SCREEN_HEIGHT-PongConstants::PADDLE_HEIGHT && leftPaddle.getVY() > 0))
	{
		leftPaddle.setVelocity(leftPaddle.getVX(), 0);
	}


	if ((rightPaddle.getY() <= 0 && rightPaddle.getVY() < 0) ||
			(rightPaddle.getY() >= TOP_SCREEN_HEIGHT-PongConstants::PADDLE_HEIGHT && rightPaddle.getVY() > 0))
	{
		rightPaddle.setVelocity(rightPaddle.getVX(), 0);
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
	renderer.drawScores(leftPoints, rightPoints);

	// draw all the buttons
	for (Button b : buttons)
	{
		renderer.drawButton(b);
	}

	// never delete this - always needs to be at the end of the loop.
	C3D_FrameEnd(0);
}

void Game::update()
{
	handleCollisions();
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

		update();
		draw();
	}
}

Game::~Game() {}
