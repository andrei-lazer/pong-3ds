#include "Renderer.hpp"
#include <string>

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

void Renderer::drawRect(Rect rect)
{
	C2D_SceneBegin(topScreen);
	C2D_DrawRectSolid(rect.getX(), rect.getY(), 0, rect.w, rect.h, white);
}
