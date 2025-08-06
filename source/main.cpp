#include <iostream>
#include <string>
#include <citro2d.h>

// TODO
// - fix bug where if the ball is behind a bat, it repeatedly swaps direction.
// - stop paddles from moving off screen
// - respawn ball to the middle when it hits the left or right side
// - when respawning, pause until a button on the bottom is pressed
// - give the ball some vertical speed when it hits a moving paddle
// - add AI to the right paddle
// - make the paddles and the ball faster
// - add acceleration to the paddles?
// - tests!
// - rename the app and add a nice icon
// - record a gameplay gif and add it to the readme
// - fill out the readme with things learned,

// #include "Renderer.hpp"
#include "Game.hpp"

int main()
{
	Game game;
	game.run();
}
