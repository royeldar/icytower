#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "icytower.h"
#include "gfx.h"
#include "sfx.h"
#include "options.h"
#include "characters.h"
#include "floor_types.h"
#include "physics.h"
#include "highscore.h"

IT_STATE it_state;
int keys;

static int rank_score, rank_floor, rank_combo;
static unsigned int val_score, val_floor, val_combo;
static char entry_name[3] = "AA";
static char last_name[3]  = "AA";
static int  name_pos;
static int  hs_view;

enum {
	ANIMATION_IDLE,
	ANIMATION_CHOCK,
	ANIMATION_WALK_LEFT,
	ANIMATION_WALK_RIGHT,
	ANIMATION_FLY,
	ANIMATION_FLY_LEFT,
	ANIMATION_FLY_RIGHT,
	ANIMATION_ROTATE
} animation;

int animation_frame;

void initialize_game(void) {
	init_state(&it_state, rejump, time(NULL));
	keys = 0;
	animation = ANIMATION_IDLE;
	animation_frame = 0;
	memcpy(last_name, hs_last_name, 3);
}

void press_left(void) { keys |= KEY_LEFT; }
void press_right(void) { keys |= KEY_RIGHT; }
void press_jump(void) { keys |= KEY_JUMP; }
void release_left(void) { keys &= ~KEY_LEFT; }
void release_right(void) { keys &= ~KEY_RIGHT; }
void release_jump(void) { keys &= ~KEY_JUMP; }

void do_tick(void) {
	int prev_status = it_state.status;
	int prev_floor = it_state.floor;
	int prev_combo_timer = it_state.combo_timer;
	if (!play_frame(&it_state, keys)) {
		al_play_sample(characters[character_index].sfx.death,
				volume_sfx / 10.0, 0, 1,
				ALLEGRO_PLAYMODE_ONCE, NULL);
		al_play_sample(sample_gameover, volume_sfx / 10.0, 0, 1,
				ALLEGRO_PLAYMODE_ONCE, NULL);
		val_score  = it_state.floor * 10 + it_state.score;
		val_floor  = it_state.floor;
		val_combo  = it_state.combo;
		rank_score = highscore_submit(&hs_score, val_score);
		rank_floor = highscore_submit(&hs_floor, val_floor);
		rank_combo = highscore_submit(&hs_combo, val_combo);
		memcpy(entry_name, last_name, 3);
		name_pos = 0;
		game_state = NAME_ENTRY;
		return;
	}

	if (it_state.speed_counter == 1500) {
		al_play_sample(sample_ring, volume_sfx / 10.0, 0, 1,
				ALLEGRO_PLAYMODE_ONCE, NULL);
		al_play_sample(sample_hurryup, volume_sfx / 10.0, 0, 1,
				ALLEGRO_PLAYMODE_ONCE, NULL);
	}

	if (it_state.floor <= 1000 ? it_state.floor / 50 > prev_floor / 50 :
			it_state.floor / 500 > prev_floor / 500)
		al_play_sample(sample_aight, volume_sfx / 10.0, 0, 1,
				ALLEGRO_PLAYMODE_ONCE, NULL);

	if (prev_combo_timer > 0 && it_state.combo_timer == 0
			&& it_state.combo_count > 1) {
		if (it_state.combo_floor >= 200)
			al_play_sample(sample_unbelievable, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 140)
			al_play_sample(sample_splendid, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 100)
			al_play_sample(sample_fantastic, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 70)
			al_play_sample(sample_extreme, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 50)
			al_play_sample(sample_amazing, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 35)
			al_play_sample(sample_wow, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 25)
			al_play_sample(sample_super, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 15)
			al_play_sample(sample_great, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else if (it_state.combo_floor >= 7)
			al_play_sample(sample_sweet, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		else
			al_play_sample(sample_good, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

	switch (it_state.status) {
	case STATUS_IDLE:
		if (it_state.dx > 0.045) {
			if (animation != ANIMATION_WALK_RIGHT) {
				animation = ANIMATION_WALK_RIGHT;
				animation_frame = 0;
			}
		} else if (it_state.dx < -0.045) {
			if (animation != ANIMATION_WALK_LEFT) {
				animation = ANIMATION_WALK_LEFT;
				animation_frame = 0;
			}
		} else if (it_state.y >= 406 && it_state.speed > 0) {
			if (animation != ANIMATION_CHOCK) {
				animation = ANIMATION_CHOCK;
				animation_frame = 0;
			}
		} else {
			if (animation != ANIMATION_IDLE) {
				animation = ANIMATION_IDLE;
				animation_frame = 0;
			}
		}
		if (prev_status != STATUS_IDLE)
			al_play_sample(sample_step, volume_sfx / 10.0,
					0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		break;
	case STATUS_FLY_UP:
		if (prev_status == STATUS_IDLE) {
			if (it_state.dy < -22.2)
				al_play_sample(characters[character_index].sfx.jumphi,
						volume_sfx / 10.0, 0, 1,
						ALLEGRO_PLAYMODE_ONCE, NULL);
			else if (it_state.dy < -15.6)
				al_play_sample(characters[character_index].sfx.jumpmed,
						volume_sfx / 10.0, 0, 1,
						ALLEGRO_PLAYMODE_ONCE, NULL);
			else
				al_play_sample(characters[character_index].sfx.jumplo,
						volume_sfx / 10.0, 0, 1,
						ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	case STATUS_FLY_IDLE:
	case STATUS_FLY_DOWN:
		if (animation == ANIMATION_ROTATE)
			break;
		if (it_state.dy < -22.2) {
			animation = ANIMATION_ROTATE;
			animation_frame = 0;
		} else if (it_state.dx > 0.045) {
			if (animation != ANIMATION_FLY_RIGHT) {
				animation = ANIMATION_FLY_RIGHT;
				animation_frame = 0;
			}
		} else if (it_state.dx < -0.045) {
			if (animation != ANIMATION_FLY_LEFT) {
				animation = ANIMATION_FLY_LEFT;
				animation_frame = 0;
			}
		} else {
			if (animation != ANIMATION_FLY &&
					animation != ANIMATION_FLY_LEFT &&
					animation != ANIMATION_FLY_RIGHT) {
				animation = ANIMATION_FLY;
				animation_frame = 0;
			}
		}
		break;
	}
	++animation_frame;
}

void draw_background(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void draw_floor(FLOOR *floor, unsigned int n) {
	int x, y = it_state.screen_y + 426 - 80 * n;
	unsigned int index = start_floor + n / 100;
	const struct floor_type *type;
	if (index >= floor_types_count)
		index = floor_types_count - 1;
	type = &floor_types[index];
	x = (floor->start + 1) * 16;
	al_draw_bitmap(type->left,
			x - al_get_bitmap_width(type->left), y, 0);
	while (x < floor->end * 16) {
		al_draw_bitmap(type->mid, x, y, 0);
		x += 16;
	}
	al_draw_bitmap(type->right, x, y, 0);
	if (n > 0 && n % 10 == 0) {
		x = (floor->start + floor->end) * 8;
		y += 16;
		al_draw_bitmap(type->sign, x, y, 0);
		x += al_get_bitmap_width(type->sign) / 2;
		y += 6;
		al_draw_textf(font_native, al_map_rgb(0, 0, 0), x - 1, y,
				ALLEGRO_ALIGN_CENTRE, "%u", n);
		al_draw_textf(font_native, al_map_rgb(0, 0, 0), x + 1, y,
				ALLEGRO_ALIGN_CENTRE, "%u", n);
		al_draw_textf(font_native, al_map_rgb(0, 0, 0), x, y - 1,
				ALLEGRO_ALIGN_CENTRE, "%u", n);
		al_draw_textf(font_native, al_map_rgb(0, 0, 0), x, y + 1,
				ALLEGRO_ALIGN_CENTRE, "%u", n);
		al_draw_textf(font_native, al_map_rgb(255, 255, 255), x, y,
				ALLEGRO_ALIGN_CENTRE, "%u", n);
	}
}

void draw_floors(void) {
	unsigned int i;
	FLOORS *floors = &it_state.floors;
	for (i = 1; i <= floors->count; ++i) {
		if (i > 7)
			break;
		draw_floor(&floors->floor[(floors->start - i + 7) % 7],
				floors->count - i);
	}
}

void draw_character(void) {
	ALLEGRO_BITMAP *character;
	int width, height;
	switch (animation) {
	case ANIMATION_IDLE:
		switch ((animation_frame / 13) % 4) {
		case 0:
		case 2:
			character = characters[character_index].gfx.idle1;
			break;
		case 1:
			character = characters[character_index].gfx.idle2;
			break;
		case 3:
			character = characters[character_index].gfx.idle3;
			break;
		}
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				0);
		break;
	case ANIMATION_CHOCK:
		character = characters[character_index].gfx.chock;
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				0);
		break;
	case ANIMATION_WALK_LEFT:
		switch ((animation_frame / 10) % 4) {
		case 0:
			character = characters[character_index].gfx.walk1;
			break;
		case 1:
			character = characters[character_index].gfx.walk2;
			break;
		case 2:
			character = characters[character_index].gfx.walk3;
			break;
		case 3:
			character = characters[character_index].gfx.walk4;
			break;
		}
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				ALLEGRO_FLIP_HORIZONTAL);
		break;
	case ANIMATION_WALK_RIGHT:
		switch ((animation_frame / 10) % 4) {
		case 0:
			character = characters[character_index].gfx.walk1;
			break;
		case 1:
			character = characters[character_index].gfx.walk2;
			break;
		case 2:
			character = characters[character_index].gfx.walk3;
			break;
		case 3:
			character = characters[character_index].gfx.walk4;
			break;
		}
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				0);
		break;
	case ANIMATION_FLY:
		character = characters[character_index].gfx.jump;
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				0);
		break;
	case ANIMATION_FLY_LEFT:
		switch (it_state.status) {
		case STATUS_FLY_UP:
			character = characters[character_index].gfx.jump1;
			break;
		case STATUS_FLY_IDLE:
			character = characters[character_index].gfx.jump2;
			break;
		case STATUS_FLY_DOWN:
			character = characters[character_index].gfx.jump3;
			break;
		}
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				ALLEGRO_FLIP_HORIZONTAL);
		break;
	case ANIMATION_FLY_RIGHT:
		switch (it_state.status) {
		case STATUS_FLY_UP:
			character = characters[character_index].gfx.jump1;
			break;
		case STATUS_FLY_IDLE:
			character = characters[character_index].gfx.jump2;
			break;
		case STATUS_FLY_DOWN:
			character = characters[character_index].gfx.jump3;
			break;
		}
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_bitmap(character,
				it_state.x - width / 2 + 1,
				it_state.y - height + 1,
				0);
		break;
	case ANIMATION_ROTATE:
		character = characters[character_index].gfx.rotate;
		width = al_get_bitmap_width(character);
		height = al_get_bitmap_height(character);
		al_draw_rotated_bitmap(character,
				width / 2, height / 2,
				it_state.x, it_state.y - height / 2,
				ALLEGRO_PI * (animation_frame % 30) / 15.0, 0);
		break;
	}
}

void draw_walls(void) {
	int y = -((80 - it_state.screen_y % 80) % 80) * 1.55;
	for (; y < 480; y += 124) {
		al_draw_bitmap(bitmap_sideblock, 640 - 75, y, 0);
		al_draw_bitmap(bitmap_sideblock,
				75 - al_get_bitmap_width(bitmap_sideblock), y,
				ALLEGRO_FLIP_HORIZONTAL);
	}
}

void draw_hud(void) {
	static unsigned int combo_timeout_count = 0;
	al_draw_bitmap(bitmap_clock, 4, 10, 0);
	al_draw_rotated_bitmap(bitmap_clock_hand, 8, 29, 40, 57,
			ALLEGRO_PI * it_state.speed_counter / 750.0, 0);

	al_draw_textf(font_color, al_map_rgb(255, 255, 255),
			8, 440, 0, "SCORE: %d",
			it_state.floor * 10 + it_state.score);

	al_draw_bitmap(bitmap_combo_meter, 20, 100, 0);
	if (it_state.combo_timer > 0) {
		al_draw_bitmap_region(bitmap_combo_liquid,
				0, 100 - it_state.combo_timer,
				16, it_state.combo_timer,
				31, 219 - it_state.combo_timer, 0);
		al_draw_bitmap(bitmap_combo_count, -10, 210, 0);
		al_draw_textf(font_color, al_map_rgb(255, 255, 255),
				40, 214, ALLEGRO_ALIGN_CENTRE,
				"%u", it_state.combo_floor);
		combo_timeout_count = 0;
	} else if (it_state.combo_count > 1) {
		if (combo_timeout_count++ < 75) {
			al_draw_bitmap(bitmap_combo_count, -10, 210, 0);
			al_draw_textf(font_color, al_map_rgb(255, 255, 255),
					40, 214, ALLEGRO_ALIGN_CENTRE,
					"%u", it_state.combo_floor);
		}
	}
}

void draw_game(void) {
	if (fullscreen)
		al_clear_to_color(al_map_rgb(20, 20, 20));
	draw_background();
	draw_floors();
	draw_character();
	draw_walls();
	draw_hud();
}

void draw_grid(void) {
}

void draw_pause(void) {
	draw_game();
	draw_grid();
	al_draw_text(font_color, al_map_rgb(255, 255, 255),
			190, 160, 0, "GAME PAUSED");
	al_draw_text(font_mono, al_map_rgb(255, 255, 255),
			132, 210, 0, "PRESS ANY KEY TO RESUME");
}

void draw_escape(void) {
	draw_game();
	draw_grid();
	al_draw_text(font_color, al_map_rgb(255, 255, 255),
			23, 160, 0, "DO YOU REALLY WANT TO EXIT?");
	al_draw_text(font_mono, al_map_rgb(255, 255, 255),
			132, 210, 0, "PRESS ANY KEY TO RESUME");
	al_draw_text(font_mono, al_map_rgb(255, 255, 255),
			190, 240, 0, "PRESS ESC TO EXIT");
}

void draw_gameover(void) {
	draw_game();
	al_draw_bitmap(bitmap_gameover, 96, 145, 0);

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	al_draw_text(font_color, white, 140, 245, 0, "SCORE:");
	al_draw_textf(font_color, white, 500, 245, ALLEGRO_ALIGN_RIGHT,
			"%u", it_state.floor * 10 + it_state.score);
	if (rank_score > 0)
		al_draw_textf(font_color, white, 510, 245, 0, "(#%d)", rank_score);

	al_draw_text(font_color, white, 140, 285, 0, "LEVEL:");
	al_draw_textf(font_color, white, 500, 285, ALLEGRO_ALIGN_RIGHT,
			"%u", it_state.floor);
	if (rank_floor > 0)
		al_draw_textf(font_color, white, 510, 285, 0, "(#%d)", rank_floor);

	al_draw_text(font_color, white, 140, 325, 0, "BEST COMBO:");
	al_draw_textf(font_color, white, 500, 325, ALLEGRO_ALIGN_RIGHT,
			"%u", it_state.combo);
	if (rank_combo > 0)
		al_draw_textf(font_color, white, 510, 325, 0, "(#%d)", rank_combo);
}

/* ---- name entry ---- */

void name_entry_up(void) {
	entry_name[name_pos] = entry_name[name_pos] == 'Z'
			? 'A' : entry_name[name_pos] + 1;
}

void name_entry_down(void) {
	entry_name[name_pos] = entry_name[name_pos] == 'A'
			? 'Z' : entry_name[name_pos] - 1;
}

void name_entry_prev(void) {
	if (name_pos > 0) name_pos--;
}

void name_entry_next(void) {
	if (name_pos == 0) {
		name_pos = 1;
		return;
	}
	/* finalize */
	entry_name[2] = '\0';
	highscore_save_last_name(entry_name);

	if (rank_score > 0)
		memcpy(hs_score.entries[rank_score - 1].name, entry_name, 3);
	if (rank_floor > 0)
		memcpy(hs_floor.entries[rank_floor - 1].name, entry_name, 3);
	if (rank_combo > 0)
		memcpy(hs_combo.entries[rank_combo - 1].name, entry_name, 3);
	highscore_save();

	PLAYER_DATA *player = highscore_find_or_create_player(entry_name);
	if (player) {
		highscore_submit_personal(&player->score, val_score);
		highscore_submit_personal(&player->floor, val_floor);
		highscore_submit_personal(&player->combo, val_combo);
		highscore_save_player(player);
	}
	game_state = GAMEOVER;
}

void draw_name_entry(void) {
	draw_gameover();
	/* vertically centred between bottom score line (325) and screen bottom (480) */
	int label_y  = 383;
	int letter_y = 410;
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR dim   = al_map_rgb(110, 110, 110);

	al_draw_text(font_color, white, 320, label_y, ALLEGRO_ALIGN_CENTRE,
			"ENTER YOUR NAME");
	for (int i = 0; i < 2; i++) {
		int lx = 295 + i * 40;
		if (i == name_pos) {
			al_draw_textf(font_color, white, lx, letter_y,
					ALLEGRO_ALIGN_CENTRE, "%c", entry_name[i]);
			al_draw_text(font_mono, white, lx, letter_y + 18,
					ALLEGRO_ALIGN_CENTRE, "_");
		} else {
			al_draw_textf(font_color, dim, lx, letter_y,
					ALLEGRO_ALIGN_CENTRE, "%c", entry_name[i]);
		}
	}
}

/* ---- highscore screen ---- */

void hs_view_left(void) {
	hs_view = (hs_view == 0) ? (int)player_count : hs_view - 1;
}

void hs_view_right(void) {
	hs_view = (hs_view >= (int)player_count) ? 0 : hs_view + 1;
}

/*
 * Column layout (cx = column centre, column width ~213px):
 *   global view  — value right at cx-26, name at cx-20, date at cx+2
 *   player view  — value right at cx-10, date at cx+4
 * Entries start half a row above where title+gap would normally place them.
 */
/* shift > 0: date moves right (score/floor)
 * shift < 0: value+name move left by same amount (combo) */
static void draw_hs_column(HIGHSCORE_LIST *list, const char *title,
		int cx, int y, bool show_names, int shift) {
	char datebuf[9];
	int value_x = cx - 35 + (shift < 0 ? shift : 0);
	int name_x  = cx - 29 + (shift < 0 ? shift : 0);
	int date_x  = cx +  2 + (shift > 0 ? shift : 0);
	int first_y = y + 50;

	al_draw_text(font_color, al_map_rgb(255, 220, 0),
			cx, y, ALLEGRO_ALIGN_CENTRE, title);

	for (unsigned int i = 0; i < list->count; i++) {
		struct tm *tm = localtime(&list->entries[i].date);
		strftime(datebuf, sizeof datebuf, "%d.%m.%y", tm);
		int row_y = first_y + (int)i * 22;

		al_draw_textf(font_mono, al_map_rgb(255, 255, 255),
				value_x, row_y, ALLEGRO_ALIGN_RIGHT,
				"%u", list->entries[i].value);
		if (show_names && list->entries[i].name[0])
			al_draw_text(font_mono, al_map_rgb(200, 200, 200),
					name_x, row_y, 0, list->entries[i].name);
		al_draw_text(font_mono, al_map_rgb(160, 160, 160),
				date_x, row_y, 0, datebuf);
	}
}

void draw_highscores(void) {
	al_draw_tinted_bitmap(bitmap_title_bg,
			al_map_rgba_f(0.5f, 0.5f, 0.5f, 1.0f), 0, 0, 0);
	if (hs_view == 0) {
		al_draw_text(font_color, al_map_rgb(255, 220, 0),
				320, 15, ALLEGRO_ALIGN_CENTRE, "HIGHSCORES");
		draw_hs_column(&hs_score, "SCORE", 107, 45, true,   6);
		draw_hs_column(&hs_floor, "FLOOR", 320, 45, true,   6);
		draw_hs_column(&hs_combo, "COMBO", 533, 45, true,  -6);
	} else {
		PLAYER_DATA *p = &players[hs_view - 1];
		al_draw_textf(font_color, al_map_rgb(255, 220, 0),
				320, 15, ALLEGRO_ALIGN_CENTRE, "HIGHSCORES  %s", p->name);
		draw_hs_column(&p->score, "SCORE", 107, 45, false,  6);
		draw_hs_column(&p->floor, "FLOOR", 320, 45, false,  6);
		draw_hs_column(&p->combo, "COMBO", 533, 45, false, -6);
	}
	/* 1.5 lines below last (15th) row: 45 + 50 + 14*22 + 11 + 22 = 436 */
	al_draw_text(font_mono, al_map_rgb(160, 160, 160),
			320, 436, ALLEGRO_ALIGN_CENTRE,
			"< PER PLAYER >");
}
