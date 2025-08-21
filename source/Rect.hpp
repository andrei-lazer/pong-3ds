#pragma once

#include "common.hpp"
#include <algorithm>
#include <math.h>

class Rect
{
protected:
	float x;
	float y;
	float vX;
	float vY;
public:
	Rect(float x, float y, float w, float h);
	float getX() const { return x; };
	float getY() const { return y; };
	float getVX() const { return vX; };
	float getVY() const { return vY; };

	void setVelocity(float newVX, float newVY);
	void setVelocityPolar(float mag, float angle);
	void setPosition(float newX, float newY);
	void reflectX();
	void reflectY();
	void update(float dt);
	void update();

	const float w;
	const float h;
};

class Ball : public Rect
{
	public:
		Ball(float x, float y, float w, float h) : Rect(x, y, w, h) {}
		void applySpin(float paddleVY);
		void randomVelocity();
};

class Paddle : public Rect
{
	public:
		Paddle(float x, float y, float w, float h) : Rect(x, y, w, h) {}
		void moveUp();
		void moveDown();
		void stop();
};
