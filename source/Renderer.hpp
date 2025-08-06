#pragma once

#include "citro2d.h"
#include <map>
#include <string>

#include "common.hpp"
#include "SolidRect.hpp"
// #include "Font.hpp"
// #include "Card.hpp"
// #include "Button.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void init();
	void initFrame();
	void clearTopScreen();
	void clearBottomScreen();
	void drawRect(Rect rect);
	void drawScores(int leftScore, int rightScore);
private:
    C2D_TextBuf C2DTextBuf;
    C2D_Text C2DText;
    C3D_RenderTarget* topScreen;
    C3D_RenderTarget* bottomScreen;
};
