#include "SolidRect.hpp"
#include "common.hpp"
#include <algorithm>
#include <math.h>

Rect::Rect(float x, float y, float w, float h)
	: x(x), y(y), w(w), h(h)
{}

void Rect::setVelocityCartesian(float newVX, float newVY)
{
	vX = newVX;
	vY = newVY;
}

void Rect::setVelocityPolar(float mag, float angle)
{

}

void Rect::updatePos()
{
	if ((x <= TOP_SCREEN_WIDTH && vX > 0) ||
	    (x >= 0 && vX < 0))
	{
		x += vX;
	}

	if ((y <= TOP_SCREEN_HEIGHT-h && vY > 0) ||
	    (y >= 0 && vY < 0))
	{
		y += vY;
	}

	// if (x <= TOP_SCREEN_WIDTH && x >= 0)
	// {
	// 	x += vX;
	// }
	// y += vY;
}
