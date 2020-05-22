#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#include "menu.h"
#include "icytower.h"
#include "gfx.h"
#include "sfx.h"
#include "options.h"
#include "characters.h"
#include "floor_types.h"
#include "fullscreen.h"

enum {
	MAIN_MENU, OPTIONS, GAME_OPTIONS, GFX_OPTIONS, SOUND_OPTIONS, CONTROLS
} menu_page = MAIN_MENU;

unsigned int menu_bullet = 0;

void menu_up(void) {
	al_play_sample(sample_menu_choose, volume_sfx / 10.0, 0, 1,
			ALLEGRO_PLAYMODE_ONCE, NULL);
	if (menu_bullet != 0)
		menu_bullet -= 1;
	else switch (menu_page) {
	case MAIN_MENU:
	case OPTIONS:
		menu_bullet = 4;
		break;
	case GAME_OPTIONS:
	case GFX_OPTIONS:
	case SOUND_OPTIONS:
		menu_bullet = 2;
		break;
	case CONTROLS:
		menu_bullet = 5;
		break;
	}
}

void menu_down(void) {
	al_play_sample(sample_menu_choose, volume_sfx / 10.0, 0, 1,
			ALLEGRO_PLAYMODE_ONCE, NULL);
	menu_bullet += 1;
	switch (menu_page) {
	case MAIN_MENU:
	case OPTIONS:
		menu_bullet %= 5;
		break;
	case GAME_OPTIONS:
	case GFX_OPTIONS:
	case SOUND_OPTIONS:
		menu_bullet %= 3;
		break;
	case CONTROLS:
		menu_bullet %= 6;
		break;
	}
}

void menu_enter(void) {
	switch (menu_page) {
	case MAIN_MENU:
		switch (menu_bullet) {
		case 0:
			/* START GAME */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			game_state = PLAYING;
			start_game();
			break;
		case 1:
			/* LOAD REPLAY */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			printf("Loading replays is not implemented yet\n");
			break;
		case 2:
			/* INSTRUCTIONS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			game_state = INSTRUCTIONS;
			break;
		case 3:
			/* OPTIONS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 0;
			break;
		case 4:
			/* EXIT */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			game_state = EXIT;
			break;
		}
		break;
	case OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* GAME OPTIONS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = GAME_OPTIONS;
			menu_bullet = 0;
			break;
		case 1:
			/* GFX OPTIONS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = GFX_OPTIONS;
			menu_bullet = 0;
			break;
		case 2:
			/* SOUND OPTIONS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = SOUND_OPTIONS;
			menu_bullet = 0;
			break;
		case 3:
			/* CONTROLS */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = CONTROLS;
			menu_bullet = 0;
			break;
		case 4:
			/* BACK */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = MAIN_MENU;
			menu_bullet = 3;
			break;
		}
		break;
	case GAME_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* CHARACTER */
			break;
		case 1:
			/* START FLOOR */
			break;
		case 2:
			/* BACK */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 0;
			break;
		}
		break;
	case GFX_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* EYE CANDY */
			break;
		case 1:
			/* FULLSCREEN */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			fullscreen = !fullscreen;
			if (fullscreen)
				enable_fullscreen();
			else
				disable_fullscreen();
			break;
		case 2:
			/* BACK */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 1;
			break;
		}
		break;
	case SOUND_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* SOUND */
			break;
		case 1:
			/* MUSIC */
			break;
		case 2:
			/* BACK */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 2;
			break;
		}
		break;
	case CONTROLS:
		switch (menu_bullet) {
		case 0:
			/* LEFT */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			printf("Changing controls is not implemented yet\n");
			break;
		case 1:
			/* RIGHT */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			printf("Changing controls is not implemented yet\n");
			break;
		case 2:
			/* JUMP */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			printf("Changing controls is not implemented yet\n");
			break;
		case 3:
			/* PAUSE */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			printf("Changing controls is not implemented yet\n");
			break;
		case 4:
			/* REJUMP */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			rejump = !rejump;
			break;
		case 5:
			/* BACK */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 3;
			break;
		}
		break;
	}
}

void menu_left(void) {
	switch (menu_page) {
	case GAME_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* CHARACTER */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (character_index > 0)
				--character_index;
			break;
		case 1:
			/* START FLOOR */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (start_floor > 0)
				--start_floor;
			break;
		}
		break;
	case GFX_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* EYE CANDY */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (eye_candy > 0)
				--eye_candy;
			break;
		}
		break;
	case SOUND_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* SOUND */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (volume_sfx > 0)
				--volume_sfx;
			break;
		case 1:
			/* MUSIC */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (volume_music > 0)
				--volume_music;
			al_set_audio_stream_gain(audio_stream_bg_menu,
					volume_music / 10.0);
			al_set_audio_stream_gain(audio_stream_bg_beat,
					volume_music / 10.0);
			break;
		}
		break;
	default:
		break;
	}
}

void menu_right(void) {
	switch (menu_page) {
	case GAME_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* CHARACTER */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (character_index < characters_count - 1)
				++character_index;
			break;
		case 1:
			/* START FLOOR */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (start_floor < floor_types_count - 1)
				++start_floor;
			break;
		}
		break;
	case GFX_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* EYE CANDY */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (eye_candy < 2)
				++eye_candy;
			break;
		}
		break;
	case SOUND_OPTIONS:
		switch (menu_bullet) {
		case 0:
			/* SOUND */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (volume_sfx < 10)
				++volume_sfx;
			break;
		case 1:
			/* MUSIC */
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			if (volume_music < 10)
				++volume_music;
			al_set_audio_stream_gain(audio_stream_bg_menu,
					volume_music / 10.0);
			al_set_audio_stream_gain(audio_stream_bg_beat,
					volume_music / 10.0);
			break;
		}
		break;
	default:
		break;
	}
}

void menu_escape(void) {
	switch (menu_page) {
	case MAIN_MENU:
		if (menu_bullet == 4) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			game_state = EXIT;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 4;
		}
		break;
	case OPTIONS:
		if (menu_bullet == 4) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = MAIN_MENU;
			menu_bullet = 3;
			break;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 4;
		}
		break;
	case GAME_OPTIONS:
		if (menu_bullet == 2) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 0;
			break;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 2;
		}
		break;
	case GFX_OPTIONS:
		if (menu_bullet == 2) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 1;
			break;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 2;
		}
		break;
	case SOUND_OPTIONS:
		if (menu_bullet == 2) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 2;
			break;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 2;
		}
		break;
	case CONTROLS:
		if (menu_bullet == 5) {
			al_play_sample(sample_menu_change, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_page = OPTIONS;
			menu_bullet = 3;
			break;
		} else {
			al_play_sample(sample_menu_choose, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			menu_bullet = 5;
		}
		break;
	}
}

const char *get_volume_bar(unsigned int n) {
	static char volume_bar[11];
	unsigned int i;
	for (i = 0; i < 10; ++i)
		volume_bar[i] = i < n ? '}' : '{';
	return volume_bar;
}

void draw_menu(void) {
	if (fullscreen)
		al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(bitmap_title_bg, 0, 0, 0);
	al_draw_bitmap(bitmap_title, 250, 20, 0);
	al_draw_bitmap(bitmap_menu_bullet, 4, 262 + 28 * menu_bullet, 0);
	switch (menu_page) {
	case MAIN_MENU:
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "START GAME");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "LOAD REPLAY");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "INSTRUCTIONS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 3, 0, "OPTIONS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 4, 0, "EXIT");
		break;
	case OPTIONS:
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "GAME OPTIONS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "GFX OPTIONS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "SOUND OPTIONS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 3, 0, "CONTROLS");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 4, 0, "BACK");
		break;
	case GAME_OPTIONS:
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "CHARACTER:");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "START FLOOR:");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "BACK");
		al_draw_bitmap(characters[character_index].gfx.idle1,
				330, 256, 0);
		al_draw_bitmap(floor_types[start_floor].left,
				315, 308, 0);
		al_draw_bitmap(floor_types[start_floor].mid,
				336, 308, 0);
		al_draw_bitmap(floor_types[start_floor].right,
				352, 308, 0);
		break;
	case GFX_OPTIONS:
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "EYE CANDY: %s",
				eye_candy == 0 ? "NONE" :
				eye_candy == 1 ? "SOME" :
				eye_candy == 2 ? "LOTS" :
				"");
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "FULLSCREEN: %s",
				fullscreen ? "YES" : "NO");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "BACK");
		break;
	case SOUND_OPTIONS:
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "SOUND:%s",
				get_volume_bar(volume_sfx));
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "MUSIC:%s",
				get_volume_bar(volume_music));
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "BACK");
		break;
	case CONTROLS:
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 0, 0, "LEFT:  (%s)",
				al_keycode_to_name(key_left));
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 1, 0, "RIGHT: (%s)",
				al_keycode_to_name(key_right));
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 2, 0, "JUMP:  (%s)",
				al_keycode_to_name(key_jump));
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 3, 0, "PAUSE: (%s)",
				al_keycode_to_name(key_pause));
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 4, 0, "REJUMP: %s",
				rejump ? "YES" : "NO");
		al_draw_text(font_color, al_map_rgb(255, 255, 255),
				40, 270 + 28 * 5, 0, "BACK");
		break;
	}
}

void draw_instructions(void) {
	if (fullscreen)
		al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(bitmap_title_bg, 0, 0, 0);
	al_draw_bitmap(bitmap_instructions, 0, 0, 0);
}
