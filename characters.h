#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

struct character_gfx {
	ALLEGRO_BITMAP *idle1;
	ALLEGRO_BITMAP *idle2;
	ALLEGRO_BITMAP *idle3;
	ALLEGRO_BITMAP *walk1;
	ALLEGRO_BITMAP *walk2;
	ALLEGRO_BITMAP *walk3;
	ALLEGRO_BITMAP *walk4;
	ALLEGRO_BITMAP *jump1;
	ALLEGRO_BITMAP *jump2;
	ALLEGRO_BITMAP *jump3;
	ALLEGRO_BITMAP *jump;
	ALLEGRO_BITMAP *chock;
	ALLEGRO_BITMAP *rotate;
	ALLEGRO_BITMAP *edge1;
	ALLEGRO_BITMAP *edge2;
};

struct character_sfx {
	ALLEGRO_SAMPLE *greeting;
	ALLEGRO_SAMPLE *jumplo;
	ALLEGRO_SAMPLE *jumpmed;
	ALLEGRO_SAMPLE *jumphi;
	ALLEGRO_SAMPLE *edge;
	ALLEGRO_SAMPLE *death;
	ALLEGRO_SAMPLE *pause;
	ALLEGRO_AUDIO_STREAM *bgmusic;
};

struct character {
	struct character_gfx gfx;
	struct character_sfx sfx;
};

extern const struct character *characters;
extern size_t characters_count;

void initialize_characters(void);
