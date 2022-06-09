#include "title.h"


static void logic(void);
static void draw(void);
static void drawLogo(void);

static SDL_Texture *titleTexture;
static int reveal = 0;
static int timeout;

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	
	titleTexture = loadTexture("gfx/title.png");
	
	timeout = FPS * 5;
}

static void logic(void)
{
	doBackground();
	
	if (reveal < SCREEN_HEIGHT)
	{
		reveal = reveal + 2;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE])
	{	

		initStage();
	}
}

static void draw(void)
{
	drawBackground();
	
	drawLogo();

	--timeout;
	
	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "< PRESS SPACE BAR TO JOIN GAME >");
	}
}

static void drawLogo(void)
{
	SDL_Rect r;
	
	r.x = 0;
	r.y = 0;
	
	r.h = MIN(reveal, r.h);
	
	SDL_QueryTexture(titleTexture, NULL, NULL, &r.w, &r.h);
	
	r.h = MIN(reveal, r.h);
	
	blitRect(titleTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);
}
