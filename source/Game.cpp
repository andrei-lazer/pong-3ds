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
	unpauseButton(
			BOTTOM_SCREEN_WIDTH/2-40, BOTTOM_SCREEN_HEIGHT/2-25,
			80, 50,
			"Go",
			[this]()
			{
				state = GameState::PLAYING;
				unpauseButton.visible = false;
			},
			Renderer::BOTTOM,
			black,
			white,
			1),
	state(GameState::PLAYING),
	leftPoints(0), rightPoints(0)
{
	ball.randomVelocity();
	unpauseButton.visible = false;
}

void Game::pause()
{
	// respawn sprites
	ball.setPosition(PongConstants::BALL_SPAWN_X, PongConstants::BALL_SPAWN_Y);
	leftPaddle.setPosition(PongConstants::LEFT_SPAWN_X, PongConstants::LEFT_SPAWN_Y);
	rightPaddle.setPosition(PongConstants::RIGHT_SPAWN_X, PongConstants::RIGHT_SPAWN_Y);
	// show a button on the bottom screen
	state = GameState::PAUSE;
	unpauseButton.visible = true;
	
	// start ball with random direction
	ball.randomVelocity();
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

	// check touch inputs
	touchPosition touch;
	hidTouchRead(&touch);

	// pressing button?
	Button b = unpauseButton;
	if (b.visible &&
	   (touch.px >= b.x && touch.px <= b.x + b.w) &&
	   (touch.py >= b.y && touch.py <= b.y + b.h))
	{
		b.onPress();
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
	for (auto& p : paddles)
	{
		// collided horizontally
		float paddlePrevX = p.getX() - p.getVX();
		float ballPrevX = ball.getX() - ball.getVX();
		// checks that the rectangles overlap now, but didn't the last frame
		if (!insideX(paddlePrevX, p.w, ballPrevX, ball.w)
				&& insideY(p.getY(), p.h, ball.getY(), ball.h)
				&& insideX(p.getX(), p.w, ball.getX(), ball.w))
		{
			// adds part of the velocity of the paddle to the ball as a sort of spin.
			ball.applySpin(p.getVY());
			ball.reflectX();
		}

		float paddlePrevY = p.getY() - p.getVY();
		float ballPrevY = ball.getY() - ball.getVY();
		if (!insideY(paddlePrevY, p.h, ballPrevY, ball.h)
				&& insideY(p.getY(), p.h, ball.getY(), ball.h)
				&& insideX(p.getX(), p.w, ball.getX(), ball.w))
		{
			ball.reflectY();
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
		rightPoints++;
		pause();
	}
	else if (ball.getX() >= TOP_SCREEN_WIDTH - PongConstants::BALL_SIZE)
	{
		leftPoints++;
		pause();
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
	renderer.drawButton(unpauseButton);

	// never delete this - always needs to be at the end of the loop.
	C3D_FrameEnd(0);
}

void Game::update()
{
	if (state == GameState::PLAYING)
	{
		handleCollisions();
		leftPaddle.update();
		rightPaddle.update();
		ball.update();
	}
	else if (state == GameState::PAUSE)
	{
		pause();
	}
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


