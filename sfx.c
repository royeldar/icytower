#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "sfx.h"

ALLEGRO_AUDIO_STREAM *audio_stream_bg_beat;
ALLEGRO_AUDIO_STREAM *audio_stream_bg_menu;

ALLEGRO_SAMPLE *sample_aight;
ALLEGRO_SAMPLE *sample_amazing;
ALLEGRO_SAMPLE *sample_cheer;
ALLEGRO_SAMPLE *sample_extreme;
ALLEGRO_SAMPLE *sample_fantastic;
ALLEGRO_SAMPLE *sample_gameover;
ALLEGRO_SAMPLE *sample_good;
ALLEGRO_SAMPLE *sample_great;
ALLEGRO_SAMPLE *sample_hurryup;
ALLEGRO_SAMPLE *sample_menu_change;
ALLEGRO_SAMPLE *sample_menu_choose;
ALLEGRO_SAMPLE *sample_ring;
ALLEGRO_SAMPLE *sample_splat;
ALLEGRO_SAMPLE *sample_splendid;
ALLEGRO_SAMPLE *sample_step;
ALLEGRO_SAMPLE *sample_super;
ALLEGRO_SAMPLE *sample_sweet;
ALLEGRO_SAMPLE *sample_tryagain;
ALLEGRO_SAMPLE *sample_unbelievable;
ALLEGRO_SAMPLE *sample_wow;

ALLEGRO_SAMPLE *sample_harold_edge;
ALLEGRO_SAMPLE *sample_harold_falling;
ALLEGRO_SAMPLE *sample_harold_jump_hi;
ALLEGRO_SAMPLE *sample_harold_jump_lo;
ALLEGRO_SAMPLE *sample_harold_jump_mid;
ALLEGRO_SAMPLE *sample_harold_wazup;
ALLEGRO_SAMPLE *sample_harold_yo;

ALLEGRO_AUDIO_STREAM *audio_stream_disco_dave_bg_dave;
ALLEGRO_SAMPLE *sample_disco_dave_ahey;
ALLEGRO_SAMPLE *sample_disco_dave_cmonyo;
ALLEGRO_SAMPLE *sample_disco_dave_diggin;
ALLEGRO_SAMPLE *sample_disco_dave_goinon;
ALLEGRO_SAMPLE *sample_disco_dave_ho;
ALLEGRO_SAMPLE *sample_disco_dave_stayinalive;
ALLEGRO_SAMPLE *sample_disco_dave_watchit;

ALLEGRO_AUDIO_STREAM *load_audio_stream(const char *filename) {
	return al_load_audio_stream(filename, 2, 2048);
}

#define LOAD_AUDIO_STREAM(name) (audio_stream_##name = load_audio_stream("sfx/" #name ".ogg"))

#define LOAD_SAMPLE(name) (sample_##name = al_load_sample("sfx/" #name ".ogg"))

#define LOAD_AUDIO_STREAM_CHARACTER(character, name)\
	(audio_stream_##character##_##name = load_audio_stream("sfx/" #character "/" #name ".ogg"))

#define LOAD_SAMPLE_CHARACTER(character, name)\
	(sample_##character##_##name = al_load_sample("sfx/" #character "/" #name ".ogg"))

#define DESTROY_AUDIO_STREAM(name) do {\
	al_destroy_audio_stream(audio_stream_##name);\
	audio_stream_##name = NULL;\
} while (false)

#define DESTROY_SAMPLE(name) do {\
	al_destroy_sample(sample_##name);\
	sample_##name = NULL;\
} while (false)

#define DESTROY_AUDIO_STREAM_CHARACTER(character, name) do {\
	al_destroy_audio_stream(audio_stream_##character##_##name);\
	audio_stream_##character##_##name = NULL;\
} while (false)

#define DESTROY_SAMPLE_CHARACTER(character, name) do {\
	al_destroy_sample(sample_##character##_##name);\
	sample_##character##_##name = NULL;\
} while (false)

bool sfx_load_audio_streams_and_samples(void) {
	if (!LOAD_AUDIO_STREAM(bg_beat))
		goto destroy;
	if (!LOAD_AUDIO_STREAM(bg_menu))
		goto destroy;
	if (!LOAD_SAMPLE(aight))
		goto destroy;
	if (!LOAD_SAMPLE(amazing))
		goto destroy;
	if (!LOAD_SAMPLE(cheer))
		goto destroy;
	if (!LOAD_SAMPLE(extreme))
		goto destroy;
	if (!LOAD_SAMPLE(fantastic))
		goto destroy;
	if (!LOAD_SAMPLE(gameover))
		goto destroy;
	if (!LOAD_SAMPLE(good))
		goto destroy;
	if (!LOAD_SAMPLE(great))
		goto destroy;
	if (!LOAD_SAMPLE(hurryup))
		goto destroy;
	if (!LOAD_SAMPLE(menu_change))
		goto destroy;
	if (!LOAD_SAMPLE(menu_choose))
		goto destroy;
	if (!LOAD_SAMPLE(ring))
		goto destroy;
	if (!LOAD_SAMPLE(splat))
		goto destroy;
	if (!LOAD_SAMPLE(splendid))
		goto destroy;
	if (!LOAD_SAMPLE(step))
		goto destroy;
	if (!LOAD_SAMPLE(super))
		goto destroy;
	if (!LOAD_SAMPLE(sweet))
		goto destroy;
	if (!LOAD_SAMPLE(tryagain))
		goto destroy;
	if (!LOAD_SAMPLE(unbelievable))
		goto destroy;
	if (!LOAD_SAMPLE(wow))
		goto destroy;

	if (!LOAD_SAMPLE_CHARACTER(harold, edge))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, falling))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, jump_hi))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, jump_lo))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, jump_mid))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, wazup))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(harold, yo))
		goto destroy;

	if (!LOAD_AUDIO_STREAM_CHARACTER(disco_dave, bg_dave))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, ahey))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, cmonyo))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, diggin))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, goinon))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, ho))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, stayinalive))
		goto destroy;
	if (!LOAD_SAMPLE_CHARACTER(disco_dave, watchit))
		goto destroy;

	return true;
destroy:
	sfx_destroy_audio_streams_and_samples();
	return false;
}

void sfx_destroy_audio_streams_and_samples(void) {
	DESTROY_AUDIO_STREAM(bg_beat);
	DESTROY_AUDIO_STREAM(bg_menu);
	DESTROY_SAMPLE(aight);
	DESTROY_SAMPLE(amazing);
	DESTROY_SAMPLE(cheer);
	DESTROY_SAMPLE(extreme);
	DESTROY_SAMPLE(fantastic);
	DESTROY_SAMPLE(gameover);
	DESTROY_SAMPLE(good);
	DESTROY_SAMPLE(great);
	DESTROY_SAMPLE(hurryup);
	DESTROY_SAMPLE(menu_change);
	DESTROY_SAMPLE(menu_choose);
	DESTROY_SAMPLE(ring);
	DESTROY_SAMPLE(splat);
	DESTROY_SAMPLE(splendid);
	DESTROY_SAMPLE(step);
	DESTROY_SAMPLE(super);
	DESTROY_SAMPLE(sweet);
	DESTROY_SAMPLE(tryagain);
	DESTROY_SAMPLE(unbelievable);
	DESTROY_SAMPLE(wow);

	DESTROY_SAMPLE_CHARACTER(harold, edge);
	DESTROY_SAMPLE_CHARACTER(harold, falling);
	DESTROY_SAMPLE_CHARACTER(harold, jump_hi);
	DESTROY_SAMPLE_CHARACTER(harold, jump_lo);
	DESTROY_SAMPLE_CHARACTER(harold, jump_mid);
	DESTROY_SAMPLE_CHARACTER(harold, wazup);
	DESTROY_SAMPLE_CHARACTER(harold, yo);

	DESTROY_AUDIO_STREAM_CHARACTER(disco_dave, bg_dave);
	DESTROY_SAMPLE_CHARACTER(disco_dave, ahey);
	DESTROY_SAMPLE_CHARACTER(disco_dave, cmonyo);
	DESTROY_SAMPLE_CHARACTER(disco_dave, diggin);
	DESTROY_SAMPLE_CHARACTER(disco_dave, goinon);
	DESTROY_SAMPLE_CHARACTER(disco_dave, ho);
	DESTROY_SAMPLE_CHARACTER(disco_dave, stayinalive);
	DESTROY_SAMPLE_CHARACTER(disco_dave, watchit);
}
