#pragma once

#include "citro2d.h"
#include <map>
#include <string>

#include "common.hpp"
#include "Rect.hpp"
/* #include "Button.hpp" */
class Button;

class Renderer {
	public:
		typedef enum {
			BOTTOM=0,
			TOP
		} screen_e;
		Renderer();
		~Renderer();
		void init();
		void initFrame();
		void clearTopScreen();
		void clearBottomScreen();
		void drawRect(const Rect& rect);
		void drawScores(int leftScore, int rightScore);
		void drawButton(const Button& b);
	private:
		C2D_TextBuf C2DTextBuf;
		C2D_Text C2DText;
		C3D_RenderTarget* topScreen;
		C3D_RenderTarget* bottomScreen;
		C3D_RenderTarget* enumToTarget(screen_e screen);
		void centredText(float x, float y, float xscale, float yscale, C3D_RenderTarget* screen, u32 colour, const char* string);

};
