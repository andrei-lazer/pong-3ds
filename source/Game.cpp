#include "Game.hpp"
#include "common.hpp"
#include <cmath>


Game::Game() :
	renderer(make_unique<Renderer>()),
	ball(make_unique<Ball>(
			PongConstants::BALL_SPAWN_X,
			PongConstants::BALL_SPAWN_Y,
			PongConstants::BALL_SIZE,
			PongConstants::BALL_SIZE
			)),
	leftPaddle(make_unique<Paddle>(
			PongConstants::LEFT_SPAWN_X,
			PongConstants::LEFT_SPAWN_Y,
			PongConstants::PADDLE_WIDTH,
			PongConstants::PADDLE_HEIGHT
			)),
	rightPaddle(make_unique<Paddle>(
			PongConstants::RIGHT_SPAWN_X,
			PongConstants::RIGHT_SPAWN_Y,
			PongConstants::PADDLE_WIDTH,
			PongConstants::PADDLE_HEIGHT
			)),
	unpauseButton(make_unique<Button>(
			BOTTOM_SCREEN_WIDTH/2-40, BOTTOM_SCREEN_HEIGHT/2-25,
			80, 50,
			"Press to\nserve",
			0.5,
			Renderer::BOTTOM,
			black,
			white,
			1,
			[this]()
			{
				state = GameState::PLAYING;
				unpauseButton->visible = false;
			}
			)),
	state(GameState::PAUSE),
	isCPU(true),
	cpu(make_unique<CPU>(*rightPaddle, *ball)),
	leftPoints(0), rightPoints(0)
{
	ball->randomVelocity();
	unpauseButton->visible = false;
}

void Game::pause()
{
	// respawn sprites
	ball->setPosition(PongConstants::BALL_SPAWN_X, PongConstants::BALL_SPAWN_Y);
	leftPaddle->setPosition(PongConstants::LEFT_SPAWN_X, PongConstants::LEFT_SPAWN_Y);
	rightPaddle->setPosition(PongConstants::RIGHT_SPAWN_X, PongConstants::RIGHT_SPAWN_Y);
	// show a button on the bottom screen
	state = GameState::PAUSE;
	unpauseButton->visible = true;
	
	// start ball with random direction
	ball->randomVelocity();
}

bool Game::handleInputs(u32 kDown, touchPosition touch)
{
	hidScanInput();
	kDown = hidKeysHeld();
	// return true if exiting
	if (kDown & KEY_START)
	{
		return true;
	}

	// cpu on/off if press select
	if (kDown & KEY_SELECT)
	{
		isCPU = !isCPU;
	}

	// left paddle moves w dpad/circle pad
	if (kDown & KEY_UP)
	{
		leftPaddle->moveUp();
	}
	else if (kDown & KEY_DOWN)
	{
		leftPaddle->moveDown();
	}
	else
	{
		leftPaddle->stop();
	}

	// right paddle moves with X/B, only if CPU is off
	if (!isCPU)
	{
		if (kDown & KEY_X)
		{
			rightPaddle->moveUp();
		}
		else if (kDown & KEY_B)
		{
			rightPaddle->moveDown();
		}
		else
		{
			rightPaddle->stop();
		}
	}
	else
	{
		cpu->controlPaddle();
	}

	// check touch inputs
	for (Button* b : {unpauseButton.get()})
	{
		if (b->visible &&
				(touch.px >= b->x && touch.px <= b->x + b->w) &&
				(touch.py >= b->y && touch.py <= b->y + b->h))
		{
			b->press();
		}
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
	for (Paddle* p : {leftPaddle.get(), rightPaddle.get()})
	{
		// collided horizontally
		float paddlePrevX = p->getX() - p->getVX();
		float ballPrevX = ball->getX() - ball->getVX();
		// checks that the rectangles overlap now, but didn't the last frame
		if (!insideX(paddlePrevX, p->w, ballPrevX, ball->w)
				&& insideY(p->getY(), p->h, ball->getY(), ball->h)
				&& insideX(p->getX(), p->w, ball->getX(), ball->w))
		{
			// adds part of the velocity of the paddle to the ball as a sort of spin.
			ball->applySpin(p->getVY());
			ball->reflectX();
		}

		float paddlePrevY = p->getY() - p->getVY();
		float ballPrevY = ball->getY() - ball->getVY();
		if (!insideY(paddlePrevY, p->h, ballPrevY, ball->h)
				&& insideY(p->getY(), p->h, ball->getY(), ball->h)
				&& insideX(p->getX(), p->w, ball->getX(), ball->w))
		{
			ball->reflectY();
		}
	}
}

void Game::handleCollisions()
{
	handlePaddleCollisions();

	bool bounceOffTopBottom = ball->getY() <= 0 ||
		ball->getY() >= TOP_SCREEN_HEIGHT - ball->h;
	if (bounceOffTopBottom)
	{
		ball->reflectY();
	}
	// check if a score needs to be changed
	if (ball->getX() <= 0)
	{
		rightPoints++;
		pause();
	}
	else if (ball->getX() >= TOP_SCREEN_WIDTH - PongConstants::BALL_SIZE)
	{
		leftPoints++;
		pause();
	}
}

void Game::draw()
{
	renderer->initFrame();
	renderer->clearTopScreen();
	renderer->clearBottomScreen();

	renderer->drawRect(*ball);
	renderer->drawRect(*leftPaddle);
	renderer->drawRect(*rightPaddle);

	// draw the score to the bottom screen
	renderer->drawScores(leftPoints, rightPoints);

	// draw all the buttons
	renderer->drawButton(*unpauseButton);

	// never delete this - always needs to be at the end of the draw loop.
	C3D_FrameEnd(0);
}

void Game::update()
{
	if (state == GameState::PLAYING)
	{
		handleCollisions();
		leftPaddle->update();
		rightPaddle->update();
		ball->update();
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
		hidScanInput();
		u32 kDown = hidKeysDown();
		touchPosition touch;
		hidTouchRead(&touch);

		if(handleInputs(kDown, touch))
		{
			break;
		}

		update();
		draw();
	}
}
