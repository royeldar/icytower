#include <allegro5/allegro.h>

#include "characters.h"
#include "gfx.h"
#include "sfx.h"

const struct character *characters;
size_t characters_count;

void initialize_characters(void) {
	static struct character _characters[2];
	struct character *harold = &_characters[0];
	struct character *disco_dave = &_characters[1];
	characters = _characters;
	characters_count = sizeof(_characters) / sizeof(*_characters);

	harold->gfx.idle1 = bitmap_harold_idle1;
	harold->gfx.idle2 = bitmap_harold_idle2;
	harold->gfx.idle3 = bitmap_harold_idle3;
	harold->gfx.walk1 = bitmap_harold_walk1;
	harold->gfx.walk2 = bitmap_harold_walk2;
	harold->gfx.walk3 = bitmap_harold_walk3;
	harold->gfx.walk4 = bitmap_harold_walk4;
	harold->gfx.jump1 = bitmap_harold_jump1;
	harold->gfx.jump2 = bitmap_harold_jump2;
	harold->gfx.jump3 = bitmap_harold_jump3;
	harold->gfx.jump = bitmap_harold_jump;
	harold->gfx.chock = bitmap_harold_chock;
	harold->gfx.rotate = bitmap_harold_rotate;
	harold->gfx.edge1 = bitmap_harold_edge1;
	harold->gfx.edge2 = bitmap_harold_edge2;
	harold->sfx.greeting = sample_harold_yo;
	harold->sfx.jumplo = sample_harold_jump_lo;
	harold->sfx.jumpmed = sample_harold_jump_mid;
	harold->sfx.jumphi = sample_harold_jump_hi;
	harold->sfx.edge = sample_harold_edge;
	harold->sfx.death = sample_harold_falling;
	harold->sfx.pause = sample_harold_wazup;
	harold->sfx.bgmusic = audio_stream_bg_beat;

	disco_dave->gfx.idle1 = bitmap_disco_dave_idle1;
	disco_dave->gfx.idle2 = bitmap_disco_dave_idle2;
	disco_dave->gfx.idle3 = bitmap_disco_dave_idle3;
	disco_dave->gfx.walk1 = bitmap_disco_dave_walk1;
	disco_dave->gfx.walk2 = bitmap_disco_dave_walk2;
	disco_dave->gfx.walk3 = bitmap_disco_dave_walk3;
	disco_dave->gfx.walk4 = bitmap_disco_dave_walk4;
	disco_dave->gfx.jump1 = bitmap_disco_dave_jump1;
	disco_dave->gfx.jump2 = bitmap_disco_dave_jump2;
	disco_dave->gfx.jump3 = bitmap_disco_dave_jump3;
	disco_dave->gfx.jump = bitmap_disco_dave_jump;
	disco_dave->gfx.chock = bitmap_disco_dave_chock;
	disco_dave->gfx.rotate = bitmap_disco_dave_rotate;
	disco_dave->gfx.edge1 = bitmap_disco_dave_edge1;
	disco_dave->gfx.edge2 = bitmap_disco_dave_edge2;
	disco_dave->sfx.greeting = sample_disco_dave_cmonyo;
	disco_dave->sfx.jumplo = sample_disco_dave_ho;
	disco_dave->sfx.jumpmed = sample_disco_dave_ahey;
	disco_dave->sfx.jumphi = sample_disco_dave_stayinalive;
	disco_dave->sfx.edge = sample_disco_dave_watchit;
	disco_dave->sfx.death = sample_disco_dave_diggin;
	disco_dave->sfx.pause = sample_disco_dave_goinon;
	disco_dave->sfx.bgmusic = audio_stream_disco_dave_bg_dave;
}
