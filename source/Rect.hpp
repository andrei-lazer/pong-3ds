#pragma once

class Rect
{
protected:
	float x;
	float y;
	float vX;
	float vY;
public:
	Rect(float x, float y, float w, float h);
	float getX() { return x; };
	float getY() { return y; };
	float getVX() { return vX; };
	float getVY() { return vY; };

	void setVelocity(float newVX, float newVY);
	void setVelocityPolar(float mag, float angle);
	void setPosition(float newX, float newY);
	void reflectX();
	void reflectY();
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
