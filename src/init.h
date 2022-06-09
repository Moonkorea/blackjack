#include "common.h"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

extern void initTitleBackground(void);
extern void initFonts(void);
extern void initHighscoreTable(void);
extern void initSounds(void);
extern void initStarfield(void);
extern void loadMusic(char *filename);
extern void playMusic(int loop);

extern App app;
extern Stage stage;
