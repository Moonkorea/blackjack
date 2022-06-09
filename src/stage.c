
#include "stage.h"
#include <time.h>

static void logic(void);
static void draw(void);
static void drawHud(void);

static int initgame(int);
static int shuffle(int*, int);

static int cardSet(int*, int*, int*);
static void printcard(int, int, int);

static void sequence1(int*, int*);
static void sequence2(int*, int*);
static void sequence3(int*, int*);
static void sequence4(int*, int*);
static void sequence5(int*, int*);
static void sequence6(int*, int*);

static SDL_Texture *targetterTexture;
static SDL_Texture *bettingTexture;
static SDL_Texture *lose;
static SDL_Texture *win;
static SDL_Texture *draw1;
static SDL_Texture *blackjack;
static SDL_Texture *gameover;
static SDL_Texture *surrender;

static int timeout = FPS*1;

static int *ctrl1;
static int *ctrl2;
static int *ctrl3;
static int *ctrl4;
static int *ctrl5;
static int *ctrl6;
static int *ctrl7;
static int *ctrl8;
static int *ctrl9;
static int *ctrl10;
static int *ctrl11;
static int *ctrl12;
static int *ctrl13;
static int *ctrl14;
static int *ctrl15;
static int *dctrl1;
static int *sctrl;


void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	targetterTexture = loadTexture("gfx/targetter.png");
	bettingTexture = loadTexture("gfx/betting.png");

	lose = loadTexture("gfx/lose.png");
	win = loadTexture("gfx/win.png");
	draw1 = loadTexture("gfx/draw.png");
	blackjack = loadTexture("gfx/blackjack.png");
	gameover = loadTexture("gfx/gameover.png");
	surrender = loadTexture("gfx/surrender.png");

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	initStageBackground();
	
	stage.score = 0;
	stage.totalmoney = 10;
	
}
static void logic(void)
{
}



static void draw(void)
{
	drawBackground();
	static int seed;	

	blit(bettingTexture, 340, 300);


	if ((stage.totalmoney >=1 && app.keyboard[SDL_SCANCODE_Z])|(stage.totalmoney >=3 && app.keyboard[SDL_SCANCODE_X])|
	(stage.totalmoney >=5 && app.keyboard[SDL_SCANCODE_C])|(stage.totalmoney >=10 && app.keyboard[SDL_SCANCODE_V])|
	(stage.totalmoney >0 && app.keyboard[SDL_SCANCODE_B]))
	{
		playSound(SND_SHUFFLE_SOUND, CH_PLAYER);
		bettingTexture = NULL;	
		seed = time(NULL);
	}

	
	if (bettingTexture == NULL)
	{
		initgame(seed);
	}
	
	
	drawHud();
	
	blit1(targetterTexture, app.mouse.x, app.mouse.y, 1);
}



static void drawHud(void)
{	
	
	if (app.keyboard[SDL_SCANCODE_Z] && stage.totalmoney>=1)
	{
		app.keyboard[SDL_SCANCODE_Z] = 0;
		stage.totalmoney -= 1;
		stage.bettingmoney = 1;	
	}

	if (app.keyboard[SDL_SCANCODE_X] && stage.totalmoney>=3)
	{
		stage.totalmoney -= 3;
		app.keyboard[SDL_SCANCODE_X] = 0;
		stage.bettingmoney = 3;
	}

	if (app.keyboard[SDL_SCANCODE_C] && stage.totalmoney>=5)
	{	
		stage.totalmoney -= 5;
		app.keyboard[SDL_SCANCODE_C] = 0;
		stage.bettingmoney = 5;
	}

	if (app.keyboard[SDL_SCANCODE_V] && stage.totalmoney>=10)
	{
		stage.totalmoney -= 10;
		app.keyboard[SDL_SCANCODE_V] = 0;
		stage.bettingmoney = 10;
	}

	if (app.keyboard[SDL_SCANCODE_B] && stage.totalmoney>0)
	{
		stage.bettingmoney = stage.totalmoney;
		stage.totalmoney = 0;
		app.keyboard[SDL_SCANCODE_B] = 0;
	}

	drawText(SCREEN_WIDTH/2, 600, 255, 255, 255, TEXT_CENTER, "TOTAL MONEY: %02.1f%s", stage.totalmoney, "$");
}



static int initgame(int seed)
{
	int Card[52];
 	int DealerC[10],PlayerC[10];
	
	shuffle(Card, seed);
	
	cardSet(DealerC, PlayerC, Card);
	
	sequence1(PlayerC, DealerC);
	
	return 0;
}



static int shuffle(int *Card, int seed)
{
 	int w = 0,r = 0;
 	int swit[52];
	
 	for(int i = 0; i < 52; i++) 
	{
  		swit[i] = 0;
 	}

 	srand(seed);
 	while(w < 52) 
	{
  		r = rand() % 52;
  		if(swit[r] == 0) 
		{
   			swit[r] = 1;
   			Card[w] = r + 1;
   			w++;
  		}
 	}
	return 0;
}



static int cardSet(int *DealerC, int *PlayerC, int *Card)
{
 	for(int i = 0; i < 10; i++)
 	{
  		DealerC[i] = Card[i];
  		PlayerC[i] = Card[i+10];
 	}
	return 0;
}



static void sequence1(int *PlayerC, int *DealerC)
{
	int x, y, i, j, Dsum = 0, Psum = 0;
	int Dealersum[10];
	int Playersum[10];
	x = app.mouse.x;
	y = app.mouse.y;

	for (i = 0; i < 10; i++)
	{
		switch(DealerC[i]%13)
		{
			case(1):
				Dealersum[i] = 11;
				break;
			case(2):
				Dealersum[i] = 2;
				break;
			case(3):
				Dealersum[i] = 3;
				break;
			case(4):
				Dealersum[i] = 4;
				break;
			case(5):
				Dealersum[i] = 5;
				break;
			case(6):
				Dealersum[i] = 6;
				break;
			case(7):
				Dealersum[i] = 7;
				break;
			case(8):
				Dealersum[i] = 8;
				break;
			case(9):
				Dealersum[i] = 9;
				break;
			case(10):
				Dealersum[i] = 10;
				break;
			case(11):
				Dealersum[i] = 10;
				break;
			case(12):
				Dealersum[i] = 10;
				break;
			case(0):
				Dealersum[i] = 10;
				break;
		}
	}

	for (i = 0; i < 10; i++)
	{
		switch(PlayerC[i]%13)
		{
			case(1):
				Playersum[i] = 11;
				break;
			case(2):
				Playersum[i] = 2;
				break;
			case(3):
				Playersum[i] = 3;
				break;
			case(4):
				Playersum[i] = 4;
				break;
			case(5):
				Playersum[i] = 5;
				break;
			case(6):
				Playersum[i] = 6;
				break;
			case(7):
				Playersum[i] = 7;
				break;
			case(8):
				Playersum[i] = 8;
				break;
			case(9):
				Playersum[i] = 9;
				break;
			case(10):
				Playersum[i] = 10;
				break;
			case(11):
				Playersum[i] = 10;
				break;
			case(12):
				Playersum[i] = 10;
				break;
			case(0):
				Playersum[i] = 10;
				break;	
		}
	}

	for(i = 0; Dsum < 17; i++)
	{
		Dsum += Dealersum[i];
	}
	

	Psum = Playersum[0] + Playersum[1];
	if (ctrl1 == PlayerC)
	{
		Psum += Playersum[2];
		if (ctrl3 == PlayerC)
		{
			Psum += Playersum[3];
			if(ctrl6 == PlayerC)
			{
				Psum += Playersum[4];
				if (ctrl9 == PlayerC)
				{
					Psum += Playersum[5];
					if (ctrl12 == PlayerC)
					{
						Psum += Playersum[6];
						if (ctrl15 == PlayerC)
						{
							Psum += Playersum[7];
						}
					}
				}
			}
		}
	}
	
	printcard(PlayerC[0], 400, 400);
	printcard(PlayerC[1], 500, 400);
	printcard(DealerC[0], 400, 100);
	// Hit

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{	
		if(x>640 && x<960 && y>640 && y<720)
		{
			playSound(SND_RECEIVE_SOUND, CH_PLAYER);
			ctrl1 = PlayerC;
		}
	}
	if (ctrl1 == PlayerC)
	{
		printcard(PlayerC[2], 500+100*1, 400);
	}



	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>960 && x<1280 && y>640 && y<720)
		{
			ctrl2 = PlayerC;
		}
	}
	if (ctrl2 == PlayerC)
	{
		sequence2(PlayerC, DealerC);
	}
	

	if (Psum > 21)
	{
		
		if (stage.totalmoney == 0)
		{
			if (--timeout <= 50 && --timeout >= 45)
			{
				playSound(SND_LOSE_SOUND, CH_PLAYER);
			}			
			
			
			if (--timeout <= -100)
			{
				blit(lose, 950, 400);	
			}
			

			if (--timeout <= -300)
			{
				blit(gameover, 300, 75);
				lose = NULL;
			}


			if (--timeout <= -600)
			{
				initTitle();
				initTitleBackground();
				gameover = NULL;
				timeout = FPS*1;
				dctrl1 = NULL;
				ctrl1 = NULL;
				ctrl2 = NULL;
				ctrl3 = NULL;
				ctrl4 = NULL;
				ctrl5 = NULL;
				ctrl6 = NULL;
				ctrl7 = NULL;
				ctrl8 = NULL;
				ctrl9 = NULL;
				ctrl10 = NULL;
				ctrl11 = NULL;
				ctrl12 = NULL;
				ctrl13 = NULL;
				ctrl14 = NULL;
				ctrl15 = NULL;
				lose = loadTexture("gfx/lose.png");
				bettingTexture = loadTexture("gfx/betting.png");	
			}
		}

		else
		{
			if (--timeout <= 50 && --timeout >= 45)
			{
				playSound(SND_LOSE_SOUND, CH_PLAYER);
			}

			if (--timeout <= -60)
			{
				
				blit(lose, 950, 400);
				stage.bettingmoney = 0;
			}
			
			if (--timeout <= -160)
			{
				lose = NULL;
				ctrl1 = NULL;
				ctrl2 = NULL;
				ctrl3 = NULL;
				ctrl4 = NULL;
				ctrl5 = NULL;
				ctrl6 = NULL;
				ctrl7 = NULL;
				ctrl8 = NULL;
				ctrl9 = NULL;
				ctrl10 = NULL;
				ctrl11 = NULL;
				ctrl12 = NULL;
				ctrl13 = NULL;
				ctrl14 = NULL;
				ctrl15 = NULL;
				bettingTexture = loadTexture("gfx/betting.png");
				lose = loadTexture("gfx/lose.png");
				timeout = FPS*1;
			}
		}
	}

	//surrender

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
	
		if(x>0 && x<320 && y>640 && y<720)
		{
			sctrl = PlayerC;
		}
	}

	if (sctrl == PlayerC)
	{
		blit(surrender,100,200);
		
		
		if (--timeout <= 0)
		{
			surrender = NULL;
			stage.totalmoney += (stage.bettingmoney/2);
			stage.bettingmoney = 0;
		}
		if (--timeout <= -60)
		{
			
			surrender = loadTexture("gfx/surrender.png");
			bettingTexture = loadTexture("gfx/betting.png");
			timeout = FPS*1;
			ctrl1 = NULL;
			ctrl2 = NULL;
			ctrl3 = NULL;
			ctrl4 = NULL;
			ctrl5 = NULL;
			ctrl6 = NULL;
			ctrl7 = NULL;
			ctrl8 = NULL;
			ctrl9 = NULL;
			ctrl10 = NULL;
			ctrl11 = NULL;
			ctrl12 = NULL;
			ctrl13 = NULL;
			ctrl14 = NULL;
			ctrl15 = NULL;
			sctrl = NULL;
		}
	}

    // Stand
	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>320 && x<640 && y>640 && y<720)
		{
			dctrl1 = PlayerC;
		}
	}


	if (dctrl1 == PlayerC)
	{
		if (--timeout <= 0)
		{
			drawText(100, 120, 255, 0, 0, TEXT_LEFT, "DEALER CARD");
			drawText(140, 160, 50, 255, 0, TEXT_LEFT, "OPEN !!");
		}
	
		for (j = 1; j < i;j++)
		{
			if (--timeout <= -150*j && --timeout >= -160*j)
			{
				playSound(SND_RECEIVE_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*j)
			{
				printcard(DealerC[j], 400 + 100*j, 100);
			}
		}


		if (Psum == 21 && Dsum != 21)
		{
			if (--timeout <= (-200*(j+1)+90) && --timeout >= (-200*(j+1)+70))
			{
				playSound(SND_CELEBRATE_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*(j+1))
			{
				blit(blackjack, 910, 300);
				blit(win, 930, 400);
				stage.totalmoney += (3*stage.bettingmoney);
				stage.bettingmoney =0;
			}	
		}

		else if(Psum == Dsum && Psum<= 21 )
		{
			if (--timeout <= (-200*(j+1)+90) && --timeout >= (-200*(j+1)+70))
			{
				playSound(SND_DRAW_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*(j+1))
			{
				blit(draw1, 900, 400);
				stage.totalmoney += (stage.bettingmoney);
				stage.bettingmoney =0;
			}
			
		}

		else if ( Psum > Dsum && Psum< 21)
		{
			if (--timeout <= (-200*(j+1)+90) && --timeout >= (-200*(j+1)+70))
			{
				playSound(SND_WIN_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*(j+1))
			{
				blit(win, 930, 400);
				stage.totalmoney += (2*stage.bettingmoney);
				stage.bettingmoney =0;
			}	
		}

		else if ( Dsum > 21 && Psum< 21)
		{
			if (--timeout <= (-200*(j+1)+90) && --timeout >= (-200*(j+1)+70))
			{
				playSound(SND_WIN_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*(j+1))
			{
				blit(win, 930, 400);
				stage.totalmoney += (2*stage.bettingmoney);
				stage.bettingmoney =0;
			}	
		}

		else if (Psum < Dsum && Dsum<=21 && Psum< 21)
		{
			if (--timeout <= (-200*(j+1)+90) && --timeout >= (-200*(j+1)+70))
			{
				playSound(SND_LOSE_SOUND, CH_PLAYER);
			}
			
			if (--timeout <= -200*(j+1))
			{
				blit(lose, 950, 400);
				stage.bettingmoney =0;
			}	
		}


		if (--timeout <= -300*(j+2))
		{
			if (stage.totalmoney == 0)
			{
				blit(gameover, 300, 75);

				if (--timeout <= -300*(j+4))
				{
					initTitle();
					initTitleBackground();

					timeout = FPS*1;
					dctrl1 = NULL;
					bettingTexture = loadTexture("gfx/betting.png");
					gameover = NULL;
					ctrl1 = NULL;
					ctrl2 = NULL;
					ctrl3 = NULL;
					ctrl4 = NULL;
					ctrl5 = NULL;
					ctrl6 = NULL;
					ctrl7 = NULL;
					ctrl8 = NULL;
					ctrl9 = NULL;
					ctrl10 = NULL;
					ctrl11 = NULL;
					ctrl12 = NULL;
					ctrl13 = NULL;
					ctrl14 = NULL;
					ctrl15 = NULL;
				}
			}

			else
			{
				dctrl1 = NULL;
				bettingTexture = loadTexture("gfx/betting.png");
				ctrl1 = NULL;
				ctrl2 = NULL;
				ctrl3 = NULL;
				ctrl4 = NULL;
				ctrl5 = NULL;
				ctrl6 = NULL;
				ctrl7 = NULL;
				ctrl8 = NULL;
				ctrl9 = NULL;
				ctrl10 = NULL;
				ctrl11 = NULL;
				ctrl12 = NULL;
				ctrl13 = NULL;
				ctrl14 = NULL;
				ctrl15 = NULL;
				timeout = FPS*1;
			}
		}
	}	
}



static void sequence2(int *PlayerC, int *DealerC)
{
	int x, y;
	x = app.mouse.x;
	y = app.mouse.y;


	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>640 && x<960 && y>640 && y<720)
		{
			ctrl3 = PlayerC;
		}
	}
	if (ctrl3 == PlayerC)
	{
		printcard(PlayerC[3], 500+100*2, 400);
		ctrl4 = PlayerC;
	}
	

	if (app.mouse.button[SDL_BUTTON_LEFT] && ctrl4 == PlayerC)
	{
		if(x>960 && x<1280 && y>640 && y<720)
		{
			ctrl5 = PlayerC;
		}
	}
	if (ctrl5 == PlayerC)
	{
		sequence3(PlayerC, DealerC);
	}
}



static void sequence3(int *PlayerC, int *DealerC)
{
	int x, y;
	x = app.mouse.x;
	y = app.mouse.y;

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>640 && x<960 && y>640 && y<720)
		{
			ctrl6 = PlayerC;
		}
	}
	if (ctrl6 == PlayerC)
	{
		printcard(PlayerC[4], 500+100*3, 400);
		ctrl7 = PlayerC;
	}


	if (app.mouse.button[SDL_BUTTON_LEFT] && ctrl7 == PlayerC)
	{
		if(x>960 && x<1280 && y>640 && y<720)
		{
			ctrl8 = PlayerC;
		}
	}
	if (ctrl8 == PlayerC)
	{
		sequence4(PlayerC, DealerC);
	}
}


static void sequence4(int *PlayerC, int *DealerC)
{
	int x, y;
	x = app.mouse.x;
	y = app.mouse.y;

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>640 && x<960 && y>640 && y<720)
		{
			ctrl9 = PlayerC;
		}
	}
	if (ctrl9 == PlayerC)
	{
		printcard(PlayerC[5], 100*3, 500);
		ctrl10 = PlayerC;
	}


	if (app.mouse.button[SDL_BUTTON_LEFT] && ctrl10 == PlayerC)
	{
		if(x>960 && x<1280 && y>640 && y<720)
		{
			ctrl11 = PlayerC;
		}
	}
	if (ctrl11 == PlayerC)
	{
		sequence5(PlayerC, DealerC);
	}
}


static void sequence5(int *PlayerC, int *DealerC)
{
	int x, y;
	x = app.mouse.x;
	y = app.mouse.y;

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>640 && x<960 && y>640 && y<720)
		{
			ctrl12 = PlayerC;
		}
	}
	if (ctrl12 == PlayerC)
	{
		printcard(PlayerC[6], 100*2, 500);
		ctrl13 = PlayerC;
	}


	if (app.mouse.button[SDL_BUTTON_LEFT] && ctrl13 == PlayerC)
	{
		if(x>960 && x<1280 && y>640 && y<720)
		{
			ctrl14 = PlayerC;
		}
	}
	if (ctrl14 == PlayerC)
	{
		sequence6(PlayerC, DealerC);
	}
}


static void sequence6(int *PlayerC, int *DealerC)
{
	int x, y;
	x = app.mouse.x;
	y = app.mouse.y;

	if (app.mouse.button[SDL_BUTTON_LEFT])
	{
		if(x>640 && x<960 && y>640 && y<720)
		{
			ctrl15 = PlayerC;
		}
	}
	if (ctrl15 == PlayerC)
	{
		printcard(PlayerC[7], 100, 500);
	}
}


static void printcard(int i, int j, int k)
{
	switch (i)
	{
		case 1:
		blit(loadTexture("gfx/1.jpg"), j, k);
		break;

		case 2:
		blit(loadTexture("gfx/2.jpg"), j, k);
		break;

		case 3:
		blit(loadTexture("gfx/3.jpg"), j, k);
		break;

		case 4:
		blit(loadTexture("gfx/4.jpg"), j, k);
		break;

		case 5:
		blit(loadTexture("gfx/5.jpg"), j, k);
		break;

		case 6:
		blit(loadTexture("gfx/6.jpg"), j, k);
		break;

		case 7:
		blit(loadTexture("gfx/7.jpg"), j, k);
		break;

		case 8:
		blit(loadTexture("gfx/8.jpg"), j, k);
		break;

		case 9:
		blit(loadTexture("gfx/9.jpg"), j, k);
		break;

		case 10:
		blit(loadTexture("gfx/10.jpg"), j, k);
		break;

		case 11:
		blit(loadTexture("gfx/11.jpg"), j, k);
		break;

		case 12:
		blit(loadTexture("gfx/12.jpg"), j, k);
		break;

		case 13:
		blit(loadTexture("gfx/13.jpg"), j, k);
		break;

		case 14:
		blit(loadTexture("gfx/14.jpg"), j, k);
		break;

		case 15:
		blit(loadTexture("gfx/15.jpg"), j, k);
		break;

		case 16:
		blit(loadTexture("gfx/16.jpg"), j, k);
		break;

		case 17:
		blit(loadTexture("gfx/17.jpg"), j, k);
		break;

		case 18:
		blit(loadTexture("gfx/18.jpg"), j, k);
		break;

		case 19:
		blit(loadTexture("gfx/19.jpg"), j, k);
		break;

		case 20:
		blit(loadTexture("gfx/20.jpg"), j, k);
		break;

		case 21:
		blit(loadTexture("gfx/21.jpg"), j, k);
		break;

		case 22:
		blit(loadTexture("gfx/22.jpg"), j, k);
		break;

		case 23:
		blit(loadTexture("gfx/23.jpg"), j, k);
		break;

		case 24:
		blit(loadTexture("gfx/24.jpg"), j, k);
		break;

		case 25:
		blit(loadTexture("gfx/25.jpg"), j, k);
		break;

		case 26:
		blit(loadTexture("gfx/26.jpg"), j, k);
		break;

		case 27:
		blit(loadTexture("gfx/27.jpg"), j, k);
		break;

		case 28:
		blit(loadTexture("gfx/28.jpg"), j, k);
		break;

		case 29:
		blit(loadTexture("gfx/29.jpg"), j, k);
		break;

		case 30:
		blit(loadTexture("gfx/30.jpg"), j, k);
		break;

		case 31:
		blit(loadTexture("gfx/31.jpg"), j, k);
		break;

		case 32:
		blit(loadTexture("gfx/32.jpg"), j, k);
		break;

		case 33:
		blit(loadTexture("gfx/33.jpg"), j, k);
		break;

		case 34:
		blit(loadTexture("gfx/34.jpg"), j, k);
		break;

		case 35:
		blit(loadTexture("gfx/35.jpg"), j, k);
		break;

		case 36:
		blit(loadTexture("gfx/36.jpg"), j, k);
		break;

		case 37:
		blit(loadTexture("gfx/37.jpg"), j, k);
		break;

		case 38:
		blit(loadTexture("gfx/38.jpg"), j, k);
		break;

		case 39:
		blit(loadTexture("gfx/39.jpg"), j, k);
		break;

		case 40:
		blit(loadTexture("gfx/40.jpg"), j, k);
		break;

		case 41:
		blit(loadTexture("gfx/41.jpg"), j, k);
		break;

		case 42:
		blit(loadTexture("gfx/42.jpg"), j, k);
		break;

		case 43:
		blit(loadTexture("gfx/43.jpg"), j, k);
		break;

		case 44:
		blit(loadTexture("gfx/44.jpg"), j, k);
		break;
		case 45:
		blit(loadTexture("gfx/45.jpg"), j, k);
		break;

		case 46:
		blit(loadTexture("gfx/46.jpg"), j, k);
		break;

		case 47:
		blit(loadTexture("gfx/47.jpg"), j, k);
		break;
		case 48:
		blit(loadTexture("gfx/48.jpg"), j, k);
		break;

		case 49:
		blit(loadTexture("gfx/49.jpg"), j, k);
		break;

		case 50:
		blit(loadTexture("gfx/50.jpg"), j, k);
		break;

		case 51:
		blit(loadTexture("gfx/51.jpg"), j, k);
		break;

		case 52:
		blit(loadTexture("gfx/52.jpg"), j, k);
		break;	
	}
}