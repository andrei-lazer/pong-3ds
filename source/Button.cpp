#include "Button.hpp"

Button::Button(
	float x, float y, float w, float h,
	const char* text,
	float textScale,
	Renderer::screen_e screen,
	u32 bgColour,
	u32 borderColour,
	float borderWidth,
	Callback cb
) :
	x(x), y(y), w(w), h(h),
	text(text), textScale(textScale),
	screen(screen), bgColour(bgColour),
	borderColour(borderColour), borderWidth(borderWidth),
	visible(true),
	cb(cb) {};

void Button::press()
{
	cb();
}
