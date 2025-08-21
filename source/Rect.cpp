#include "Rect.hpp"

Rect::Rect(float x, float y, float w, float h)
	: x(x), y(y), w(w), h(h)
{}

void Rect::setVelocity(float newVX, float newVY)
{
	vX = newVX;
	vY = newVY;
}

void Rect::setPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

void Rect::setVelocityPolar(float mag, float angle)
{
	vX = mag * std::cos(angle);
	vY = mag * std::sin(angle);

}

void Rect::reflectX()
{
	vX = -vX;
}

void Rect::reflectY()
{
	vY = -vY;
}

void Rect::update(float dt)
{
	x += dt*vX;
	y += dt*vY;

	if (y < 0)
	{
		y = 0;
	}
	else if (y > TOP_SCREEN_HEIGHT - h)
	{
		y = TOP_SCREEN_HEIGHT - h;
	}
}

void Rect::update()
{
	x += vX;
	y += vY;

	if (y < 0)
	{
		y = 0;
	}
	else if (y > TOP_SCREEN_HEIGHT - h)
	{
		y = TOP_SCREEN_HEIGHT - h;
	}

}

void Ball::applySpin(float paddleVY)
{
	float angle = std::atan2(vY, vX);
	angle += paddleVY * PongConstants::BALL_SPIN_FACTOR * (vX > 0 ? 1 : -1);

	if ((std::abs(angle) > PongConstants::MAX_BALL_ANGLE) &&
		(std::abs(angle) < PI - PongConstants::MAX_BALL_ANGLE))
	{
		// ternary operator
		angle = PongConstants::MAX_BALL_ANGLE * (angle > 0 ? 1 : -1);
	}

	setVelocityPolar(PongConstants::BALL_SPEED, angle);
}

void Ball::randomVelocity()
{
	float randomAngle = randomFloat(-PongConstants::MAX_BALL_ANGLE/2, PongConstants::MAX_BALL_ANGLE/2);
	float leftOrRight = randomFloat(0, 1);
	randomAngle += (leftOrRight >= 0.5 ? PI : 0);
	setVelocityPolar(PongConstants::BALL_SPEED, randomAngle);
}

void Paddle::moveUp()
{
	vY = -PongConstants::PADDLE_SPEED;
}

void Paddle::moveDown()
{
	vY = PongConstants::PADDLE_SPEED;
}

void Paddle::stop()
{
	vY = 0;
}
