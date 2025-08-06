#include "SolidRect.hpp"
#include "common.hpp"
#include <algorithm>
#include <math.h>

Rect::Rect(float x, float y, float w, float h)
	: x(x), y(y), w(w), h(h)
{}

void Rect::setVelocity(float newVX, float newVY)
{
	vX = newVX;
	vY = newVY;
}

void Rect::reflectX()
{
	vX = -vX;
}

void Rect::reflectY()
{
	vY = -vY;
}

void Rect::update()
{
	x += vX;
	y += vY;
}
