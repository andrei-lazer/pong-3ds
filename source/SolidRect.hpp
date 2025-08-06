#pragma once

class Rect
{
private:
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
	void setVelocityCartesian(float newVX, float newVY);
	void setVelocityPolar(float mag, float angle);
	void updatePos();
	// void setPosition(float x, float y);
	const float w;
	const float h;
};
