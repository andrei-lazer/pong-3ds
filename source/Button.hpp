#pragma once

#include <functional>
#include "Renderer.hpp"

class Button
{
public:
	using Callback = std::function<void()>;
	Button(float x, float y, float w, float h, const char* text, Callback cb, Renderer::screen_e screen, u32 bgColour, u32 borderColour, float borderWidth);
	const float x, y, w, h;
	const char* text;
	const Renderer::screen_e screen;
	const u32 bgColour;
	const u32 borderColour;
	const float borderWidth;
	bool visible;
	void onPress();
private:
	Callback cb;
};
