#include "background.h"

static int backgroundX;

static SDL_Texture *background;

void initTitleBackground(void)
{
	background = loadTexture("gfx/background1.png");
	
	backgroundX = 0;
}

void initStageBackground(void)
{
	background = loadTexture("gfx/stagebackground.png");

	backgroundX = 0;
}

void doBackground(void)
{
	if (--backgroundX < -SCREEN_WIDTH)
	{
		backgroundX = 0;
	}
}


void drawBackground(void)
{
	SDL_Rect dest;
	int x;
	
	for (x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;
		
		SDL_RenderCopy(app.renderer, background, NULL, &dest);
	}
}
