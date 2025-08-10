#include "Renderer.hpp"
#include <string>
#include "Button.hpp"

Renderer::Renderer()
{
	C2DTextBuf = C2D_TextBufNew(4096);

	romfsInit();
	cfguInit();
	gfxInitDefault();

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	topScreen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

Renderer::~Renderer()
{
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}

void Renderer::initFrame()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
}

void Renderer::clearTopScreen()
{
	C2D_SceneBegin(topScreen);
	C2D_TargetClear(topScreen, background_colour);
}

void Renderer::clearBottomScreen()
{
	C2D_SceneBegin(bottomScreen);
	C2D_TargetClear(bottomScreen, background_colour);
}

void Renderer::centredText(float x, float y, float xscale, float yscale, C3D_RenderTarget* screen, u32 colour, const char* text)
{
	C2D_SceneBegin(screen);
	C2D_TextBufClear(C2DTextBuf);
	C2D_TextParse(&C2DText, C2DTextBuf, text);
	C2D_TextOptimize(&C2DText);

	float width, height;
	C2D_TextGetDimensions(&C2DText, xscale, yscale, &width, &height);

	float cornerX = x - width/2;
	float cornerY = y - height/2;

	C2D_DrawText(&C2DText, C2D_WithColor, cornerX, cornerY, 0.0f, xscale, yscale, colour);
}

void Renderer::drawRect(Rect rect)
{
	C2D_SceneBegin(topScreen);
	C2D_DrawRectSolid(rect.getX(), rect.getY(), 0, rect.w, rect.h, white);
}

void Renderer::drawScores(int leftScore, int rightScore)
{
	std::string leftString = std::to_string(leftScore);
	std::string rightString = std::to_string(rightScore);
	C2D_SceneBegin(bottomScreen);
	// left score
	C2D_TextBufClear(C2DTextBuf);
	C2D_TextParse(&C2DText, C2DTextBuf, leftString.c_str());
	C2D_TextOptimize(&C2DText);
	C2D_DrawText(&C2DText, C2D_AlignCenter | C2D_WithColor, 100, 100, 0.0f, 1.5, 1.5, white);
	// right score
	C2D_TextBufClear(C2DTextBuf);
	C2D_TextParse(&C2DText, C2DTextBuf, rightString.c_str());
	C2D_TextOptimize(&C2DText);
	C2D_DrawText(&C2DText, C2D_AlignCenter | C2D_WithColor, 200, 100, 0.0f, 1.5, 1.5, white);
}

void Renderer::drawButton(Button b)
{
	// draw the rectangle
	C2D_SceneBegin(enumToTarget(b.screen));
	// draw border
	/* C2D_DrawRectSolid(b.x, b.y, 0, b.w, b.y, b.borderColour); */
	/* C2D_DrawRectSolid(b.x+b.borderWidth, b.y+b.borderWidth, 0, b.w-b.borderWidth*2, b.y-b.borderWidth*2, b.bgColour); */
	centredText(b.x + b.w/2, b.y + b.h/2, 1, 1, bottomScreen, b.bgColour, b.text);
}

C3D_RenderTarget* Renderer::enumToTarget(screen_e screen)
{
	switch (screen)
	{
		case (BOTTOM):
			return bottomScreen;
			break;
		case (TOP):
		default:
			return topScreen;
			break;
	}
}
