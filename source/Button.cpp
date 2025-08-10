#include "Button.hpp"

Button::Button(float x, float y, float w, float h, const char* text, Callback cb, Renderer::screen_e screen, u32 bgColour, u32 borderColour, float borderWidth)
	: x(x), y(y), w(w), h(h), text(text), cb(cb), screen(screen), bgColour(bgColour), borderColour(borderColour), borderWidth(borderWidth) {};

void Button::onPress()
{
	cb();
}
