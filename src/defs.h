#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MAX_SCORE_NAME_LENGTH  16
#define MAX_NAME_LENGTH        32
#define MAX_LINE_LENGTH        1024

#define FPS 60

#define PLAYER_SPEED          10
#define PLAYER_BULLET_SPEED   200
#define ALIEN_BULLET_SPEED    800

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTONS 6

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define MAX_STARS   500

#define MAX_SND_CHANNELS 8

#define NUM_HIGHSCORES 8

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

#define ON 1

enum
{
	CH_ANY = -1,
	CH_PLAYER,
};

enum
{
	SND_SHUFFLE_SOUND,
	SND_RECEIVE_SOUND,
	SND_CELEBRATE_SOUND,
	SND_WIN_SOUND,
	SND_LOSE_SOUND,
	SND_DRAW_SOUND,
	SND_MAX
};

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};
