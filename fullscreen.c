#include <allegro5/allegro.h>

#include "fullscreen.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

void enable_fullscreen(void) {
	ALLEGRO_DISPLAY *display = al_get_current_display();
	ALLEGRO_TRANSFORM t;
	int width, height;
	float scale, offset_x, offset_y;

	al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);
	width = al_get_display_width(display);
	height = al_get_display_height(display);

	scale = MIN(width / 640.0, height / 480.0);
	offset_x = 0.5 * (width - scale * 640.0);
	offset_y = 0.5 * (height - scale * 480.0);
	al_identity_transform(&t);
	al_scale_transform(&t, scale, scale);
	al_translate_transform(&t, offset_x, offset_y);
	al_use_transform(&t);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_clipping_rectangle(offset_x + 0.5, offset_y + 0.5,
			640.0 * scale + 0.5, 480.0 * scale + 0.5);
}

void disable_fullscreen(void) {
	ALLEGRO_DISPLAY *display = al_get_current_display();
	ALLEGRO_TRANSFORM t;
	al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false);
	al_identity_transform(&t);
	al_use_transform(&t);

	al_reset_clipping_rectangle();
}
