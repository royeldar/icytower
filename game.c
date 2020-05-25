#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <time.h>

#include "game.h"
#include "gfx.h"
#include "sfx.h"
#include "options.h"
#include "characters.h"
#include "floor_types.h"
#include "physics.h"

IT_STATE it_state;
int keys;

enum {
	ANIMATION_IDLE,
	ANIMATION_CHOCK,
	ANIMATION_EDGE_LEFT,
	ANIMATION_EDGE_RIGHT,
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
}

void press_left(void) { keys |= KEY_LEFT; }
void press_right(void) { keys |= KEY_RIGHT; }
void press_jump(void) { keys |= KEY_JUMP; }
void release_left(void) { keys &= ~KEY_LEFT; }
void release_right(void) { keys &= ~KEY_RIGHT; }
void release_jump(void) { keys &= ~KEY_JUMP; }

void do_tick(void) {
	int prev_status = it_state.status;
	play_frame(&it_state, keys);
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
		break;
	case STATUS_FLY_UP:
	case STATUS_FLY_IDLE:
	case STATUS_FLY_DOWN:
		if (animation == ANIMATION_ROTATE)
			break;
		if (it_state.dy < -22.3) {
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

void draw_game(void) {
	if (fullscreen)
		al_clear_to_color(al_map_rgb(0, 0, 0));
	draw_background();
	draw_floors();
	draw_character();
}
