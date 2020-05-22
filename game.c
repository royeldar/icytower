#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <time.h>

#include "gfx.h"
#include "sfx.h"
#include "options.h"
#include "characters.h"
#include "floor_types.h"
#include "physics.h"

IT_STATE it_state;
int keys;

void initialize_game(void) {
	init_state(&it_state, rejump, time(NULL));
	keys = 0;
}

void press_left(void) { keys |= KEY_LEFT; }
void press_right(void) { keys |= KEY_RIGHT; }
void press_jump(void) { keys |= KEY_JUMP; }
void release_left(void) { keys &= ~KEY_LEFT; }
void release_right(void) { keys &= ~KEY_RIGHT; }
void release_jump(void) { keys &= ~KEY_JUMP; }

void do_tick(void) {
	play_frame(&it_state, keys);
}

void draw_background(void) {
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
	al_draw_bitmap(characters[character_index].gfx.idle1,
			it_state.x, it_state.y, 0);
}

void draw_game(void) {
	if (fullscreen)
		al_clear_to_color(al_map_rgb(0, 0, 0));
	draw_background();
	draw_floors();
	draw_character();
}
