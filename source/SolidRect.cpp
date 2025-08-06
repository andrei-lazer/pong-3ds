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
	x += vX;
	y += vY;
}
