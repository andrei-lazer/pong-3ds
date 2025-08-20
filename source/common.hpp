#pragma once

#include <cstdlib>

#define TOP_SCREEN_WIDTH 400.0f
#define TOP_SCREEN_HEIGHT 240.0f
#define BOTTOM_SCREEN_WIDTH 320.0f
#define BOTTOM_SCREEN_HEIGHT 240.0f

#define PI M_PI
// #include "c2d/base.h"
#include <citro2d.h>

const u32 white = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
const u32 black = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
const u32 green = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
const u32 red   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
const u32 blue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

const u32 background_colour = C2D_Color32(0x22, 0x31, 0x1d, 0xFF);

float randomFloat(float a, float b);

namespace PongConstants
{
	constexpr float BALL_SIZE = 10.0f;
	constexpr float BALL_SPAWN_X = TOP_SCREEN_WIDTH/2 - BALL_SIZE/2;
	constexpr float BALL_SPAWN_Y = TOP_SCREEN_HEIGHT/2 - BALL_SIZE/2;

	constexpr float PADDLE_WIDTH = 10.0f;
	constexpr float PADDLE_HEIGHT = 30.0f;

	constexpr float LEFT_SPAWN_X = 10.0f;
	constexpr float LEFT_SPAWN_Y = TOP_SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;
	constexpr float RIGHT_SPAWN_X = TOP_SCREEN_WIDTH - 10.0f - PADDLE_WIDTH;
	constexpr float RIGHT_SPAWN_Y = TOP_SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;

	constexpr float PADDLE_SPEED = 3.0f;
	constexpr float BALL_SPEED = 2.5f;

	constexpr float BALL_SPIN_FACTOR = 0.1f;
	constexpr float MAX_BALL_ANGLE = PI/3;

	constexpr float SCORE_X_DIST = 50;
	constexpr float SCORE_Y_DIST = BOTTOM_SCREEN_HEIGHT/2;
	constexpr float SCORE_SCALE = 1;
}

void testFunc();
