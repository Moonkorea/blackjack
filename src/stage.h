#include "common.h"


extern void addHighscore(int score);

extern void blit(SDL_Texture *texture, int x, int y);
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
/*
extern void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
*/
extern void doBackground(void);
extern void drawBackground(void);
extern void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);
extern void initStageBackground(void);
extern SDL_Texture *loadTexture(char *filename);
extern void playSound(int id, int channel);
extern void blit1(SDL_Texture *texture, int x, int y, int center);
extern void initTitle(void);
extern void initTitleBackground(void);
extern void loadMusic(char *filename);

extern App app;
extern Highscores highscores;
extern Stage stage;
