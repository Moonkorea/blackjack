
#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
	
	music = NULL;
	
	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
	sounds[SND_SHUFFLE_SOUND] = Mix_LoadWAV("sound/shuffle sound.ogg");
	sounds[SND_RECEIVE_SOUND] = Mix_LoadWAV("sound/give card.ogg");
	sounds[SND_WIN_SOUND] = Mix_LoadWAV("sound/win.ogg");
	sounds[SND_LOSE_SOUND] = Mix_LoadWAV("sound/lose.ogg");
	sounds[SND_DRAW_SOUND] = Mix_LoadWAV("sound/draw.ogg");
	sounds[SND_CELEBRATE_SOUND] = Mix_LoadWAV("sound/celebrate.ogg");
}
