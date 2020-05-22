#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string.h>
#include <stdio.h>

#include "gfx.h"

ALLEGRO_BITMAP *bitmap_bgtile;
ALLEGRO_BITMAP *bitmap_browse_button;
ALLEGRO_BITMAP *bitmap_bt_no;
ALLEGRO_BITMAP *bitmap_bt_yes;
ALLEGRO_BITMAP *bitmap_clock;
ALLEGRO_BITMAP *bitmap_clock_hand;
ALLEGRO_BITMAP *bitmap_combo_count;
ALLEGRO_BITMAP *bitmap_combo_liquid;
ALLEGRO_BITMAP *bitmap_combo_meter;
ALLEGRO_BITMAP *bitmap_floor01;
ALLEGRO_BITMAP *bitmap_floor02;
ALLEGRO_BITMAP *bitmap_floor03;
ALLEGRO_BITMAP *bitmap_floor04;
ALLEGRO_BITMAP *bitmap_floor05;
ALLEGRO_BITMAP *bitmap_floor06;
ALLEGRO_BITMAP *bitmap_floor07;
ALLEGRO_BITMAP *bitmap_floor08;
ALLEGRO_BITMAP *bitmap_floor09;
ALLEGRO_BITMAP *bitmap_floor10;
ALLEGRO_BITMAP *bitmap_floor11;
ALLEGRO_BITMAP *bitmap_floor12;
ALLEGRO_BITMAP *bitmap_floor12a;
ALLEGRO_BITMAP *bitmap_floor12b;
ALLEGRO_BITMAP *bitmap_floor12c;
ALLEGRO_BITMAP *bitmap_floor13;
ALLEGRO_BITMAP *bitmap_floor14;
ALLEGRO_BITMAP *bitmap_floor15;
ALLEGRO_BITMAP *bitmap_floor16;
ALLEGRO_BITMAP *bitmap_floor17;
ALLEGRO_BITMAP *bitmap_floor18;
ALLEGRO_BITMAP *bitmap_floor18a;
ALLEGRO_BITMAP *bitmap_floor18b;
ALLEGRO_BITMAP *bitmap_floor18c;
ALLEGRO_BITMAP *bitmap_floor19;
ALLEGRO_BITMAP *bitmap_floor20;
ALLEGRO_BITMAP *bitmap_floor21;
ALLEGRO_BITMAP *bitmap_floor22;
ALLEGRO_BITMAP *bitmap_floor23;
ALLEGRO_BITMAP *bitmap_floor24;
ALLEGRO_BITMAP *bitmap_floor25;
ALLEGRO_BITMAP *bitmap_floor26;
ALLEGRO_BITMAP *bitmap_floor27;
ALLEGRO_BITMAP *bitmap_gameover;
ALLEGRO_BITMAP *bitmap_heroface000;
ALLEGRO_BITMAP *bitmap_heroface001;
ALLEGRO_BITMAP *bitmap_heroface002;
ALLEGRO_BITMAP *bitmap_highscore;
ALLEGRO_BITMAP *bitmap_hint;
ALLEGRO_BITMAP *bitmap_hisctop;
ALLEGRO_BITMAP *bitmap_hurryup;
ALLEGRO_BITMAP *bitmap_instructions;
ALLEGRO_BITMAP *bitmap_menu_bullet;
ALLEGRO_BITMAP *bitmap_replay_bg;
ALLEGRO_BITMAP *bitmap_replay_buttons;
ALLEGRO_BITMAP *bitmap_reward000;
ALLEGRO_BITMAP *bitmap_reward001;
ALLEGRO_BITMAP *bitmap_reward002;
ALLEGRO_BITMAP *bitmap_reward003;
ALLEGRO_BITMAP *bitmap_reward004;
ALLEGRO_BITMAP *bitmap_reward005;
ALLEGRO_BITMAP *bitmap_reward006;
ALLEGRO_BITMAP *bitmap_reward007;
ALLEGRO_BITMAP *bitmap_reward008;
ALLEGRO_BITMAP *bitmap_reward009;
ALLEGRO_BITMAP *bitmap_sideblock;
ALLEGRO_BITMAP *bitmap_sign01;
ALLEGRO_BITMAP *bitmap_sign02;
ALLEGRO_BITMAP *bitmap_sign03;
ALLEGRO_BITMAP *bitmap_sign04;
ALLEGRO_BITMAP *bitmap_sign04a;
ALLEGRO_BITMAP *bitmap_sign05;
ALLEGRO_BITMAP *bitmap_sign06;
ALLEGRO_BITMAP *bitmap_sign06a;
ALLEGRO_BITMAP *bitmap_sign07;
ALLEGRO_BITMAP *bitmap_sign08;
ALLEGRO_BITMAP *bitmap_sign09;
ALLEGRO_BITMAP *bitmap_sort_button_all;
ALLEGRO_BITMAP *bitmap_sort_button_combo;
ALLEGRO_BITMAP *bitmap_sort_button_floor;
ALLEGRO_BITMAP *bitmap_sort_button_name;
ALLEGRO_BITMAP *bitmap_sort_button_score;
ALLEGRO_BITMAP *bitmap_star01;
ALLEGRO_BITMAP *bitmap_star02;
ALLEGRO_BITMAP *bitmap_star03;
ALLEGRO_BITMAP *bitmap_star04;
ALLEGRO_BITMAP *bitmap_star05;
ALLEGRO_BITMAP *bitmap_star06;
ALLEGRO_BITMAP *bitmap_star07;
ALLEGRO_BITMAP *bitmap_star08;
ALLEGRO_BITMAP *bitmap_title;
ALLEGRO_BITMAP *bitmap_title_bg;
ALLEGRO_BITMAP *bitmap_vcr;
ALLEGRO_BITMAP *bitmap_vcr_left;
ALLEGRO_BITMAP *bitmap_vcr_right;
ALLEGRO_BITMAP *bitmap_vcr_up;

ALLEGRO_BITMAP *bitmap_harold_chock;
ALLEGRO_BITMAP *bitmap_harold_edge1;
ALLEGRO_BITMAP *bitmap_harold_edge2;
ALLEGRO_BITMAP *bitmap_harold_idle1;
ALLEGRO_BITMAP *bitmap_harold_idle2;
ALLEGRO_BITMAP *bitmap_harold_idle3;
ALLEGRO_BITMAP *bitmap_harold_jump;
ALLEGRO_BITMAP *bitmap_harold_jump1;
ALLEGRO_BITMAP *bitmap_harold_jump2;
ALLEGRO_BITMAP *bitmap_harold_jump3;
ALLEGRO_BITMAP *bitmap_harold_rotate;
ALLEGRO_BITMAP *bitmap_harold_walk1;
ALLEGRO_BITMAP *bitmap_harold_walk2;
ALLEGRO_BITMAP *bitmap_harold_walk3;
ALLEGRO_BITMAP *bitmap_harold_walk4;

ALLEGRO_BITMAP *bitmap_disco_dave_chock;
ALLEGRO_BITMAP *bitmap_disco_dave_edge1;
ALLEGRO_BITMAP *bitmap_disco_dave_edge2;
ALLEGRO_BITMAP *bitmap_disco_dave_idle1;
ALLEGRO_BITMAP *bitmap_disco_dave_idle2;
ALLEGRO_BITMAP *bitmap_disco_dave_idle3;
ALLEGRO_BITMAP *bitmap_disco_dave_jump;
ALLEGRO_BITMAP *bitmap_disco_dave_jump1;
ALLEGRO_BITMAP *bitmap_disco_dave_jump2;
ALLEGRO_BITMAP *bitmap_disco_dave_jump3;
ALLEGRO_BITMAP *bitmap_disco_dave_rotate;
ALLEGRO_BITMAP *bitmap_disco_dave_walk1;
ALLEGRO_BITMAP *bitmap_disco_dave_walk2;
ALLEGRO_BITMAP *bitmap_disco_dave_walk3;
ALLEGRO_BITMAP *bitmap_disco_dave_walk4;

#define MASK_COLOR al_map_rgb(152, 20, 144)

ALLEGRO_BITMAP *load_bitmap(const char *filename) {
	ALLEGRO_BITMAP *bitmap = al_load_bitmap(filename);
	if (bitmap != NULL)
		al_convert_mask_to_alpha(bitmap, MASK_COLOR);
	return bitmap;
}

#define LOAD_BITMAP(name) (bitmap_##name = load_bitmap("gfx/" #name ".bmp"))

#define LOAD_BITMAP_CHARACTER(character, name)\
	(bitmap_##character##_##name = load_bitmap("gfx/" #character "/" #name ".bmp"))

#define DESTROY_BITMAP(name) do {\
	al_destroy_bitmap(bitmap_##name);\
	bitmap_##name = NULL;\
} while (false)

#define DESTROY_BITMAP_CHARACTER(character, name) do {\
	al_destroy_bitmap(bitmap_##character##_##name);\
	bitmap_##character##_##name = NULL;\
} while (false)

bool gfx_load_bitmaps(void) {
	if (!LOAD_BITMAP(bgtile))
		goto destroy;
	if (!LOAD_BITMAP(browse_button))
		goto destroy;
	if (!LOAD_BITMAP(bt_no))
		goto destroy;
	if (!LOAD_BITMAP(bt_yes))
		goto destroy;
	if (!LOAD_BITMAP(clock))
		goto destroy;
	if (!LOAD_BITMAP(clock_hand))
		goto destroy;
	if (!LOAD_BITMAP(combo_count))
		goto destroy;
	if (!LOAD_BITMAP(combo_liquid))
		goto destroy;
	if (!LOAD_BITMAP(combo_meter))
		goto destroy;
	if (!LOAD_BITMAP(floor01))
		goto destroy;
	if (!LOAD_BITMAP(floor02))
		goto destroy;
	if (!LOAD_BITMAP(floor03))
		goto destroy;
	if (!LOAD_BITMAP(floor04))
		goto destroy;
	if (!LOAD_BITMAP(floor05))
		goto destroy;
	if (!LOAD_BITMAP(floor06))
		goto destroy;
	if (!LOAD_BITMAP(floor07))
		goto destroy;
	if (!LOAD_BITMAP(floor08))
		goto destroy;
	if (!LOAD_BITMAP(floor09))
		goto destroy;
	if (!LOAD_BITMAP(floor10))
		goto destroy;
	if (!LOAD_BITMAP(floor11))
		goto destroy;
	if (!LOAD_BITMAP(floor12))
		goto destroy;
	if (!LOAD_BITMAP(floor12a))
		goto destroy;
	if (!LOAD_BITMAP(floor12b))
		goto destroy;
	if (!LOAD_BITMAP(floor12c))
		goto destroy;
	if (!LOAD_BITMAP(floor13))
		goto destroy;
	if (!LOAD_BITMAP(floor14))
		goto destroy;
	if (!LOAD_BITMAP(floor15))
		goto destroy;
	if (!LOAD_BITMAP(floor16))
		goto destroy;
	if (!LOAD_BITMAP(floor17))
		goto destroy;
	if (!LOAD_BITMAP(floor18))
		goto destroy;
	if (!LOAD_BITMAP(floor18a))
		goto destroy;
	if (!LOAD_BITMAP(floor18b))
		goto destroy;
	if (!LOAD_BITMAP(floor18c))
		goto destroy;
	if (!LOAD_BITMAP(floor19))
		goto destroy;
	if (!LOAD_BITMAP(floor20))
		goto destroy;
	if (!LOAD_BITMAP(floor21))
		goto destroy;
	if (!LOAD_BITMAP(floor22))
		goto destroy;
	if (!LOAD_BITMAP(floor23))
		goto destroy;
	if (!LOAD_BITMAP(floor24))
		goto destroy;
	if (!LOAD_BITMAP(floor25))
		goto destroy;
	if (!LOAD_BITMAP(floor26))
		goto destroy;
	if (!LOAD_BITMAP(floor27))
		goto destroy;
	if (!LOAD_BITMAP(gameover))
		goto destroy;
	if (!LOAD_BITMAP(heroface000))
		goto destroy;
	if (!LOAD_BITMAP(heroface001))
		goto destroy;
	if (!LOAD_BITMAP(heroface002))
		goto destroy;
	if (!LOAD_BITMAP(highscore))
		goto destroy;
	if (!LOAD_BITMAP(hint))
		goto destroy;
	if (!LOAD_BITMAP(hisctop))
		goto destroy;
	if (!LOAD_BITMAP(hurryup))
		goto destroy;
	if (!LOAD_BITMAP(instructions))
		goto destroy;
	if (!LOAD_BITMAP(menu_bullet))
		goto destroy;
	if (!LOAD_BITMAP(replay_bg))
		goto destroy;
	if (!LOAD_BITMAP(replay_buttons))
		goto destroy;
	if (!LOAD_BITMAP(reward000))
		goto destroy;
	if (!LOAD_BITMAP(reward001))
		goto destroy;
	if (!LOAD_BITMAP(reward002))
		goto destroy;
	if (!LOAD_BITMAP(reward003))
		goto destroy;
	if (!LOAD_BITMAP(reward004))
		goto destroy;
	if (!LOAD_BITMAP(reward005))
		goto destroy;
	if (!LOAD_BITMAP(reward006))
		goto destroy;
	if (!LOAD_BITMAP(reward007))
		goto destroy;
	if (!LOAD_BITMAP(reward008))
		goto destroy;
	if (!LOAD_BITMAP(reward009))
		goto destroy;
	if (!LOAD_BITMAP(sideblock))
		goto destroy;
	if (!LOAD_BITMAP(sign01))
		goto destroy;
	if (!LOAD_BITMAP(sign02))
		goto destroy;
	if (!LOAD_BITMAP(sign03))
		goto destroy;
	if (!LOAD_BITMAP(sign04))
		goto destroy;
	if (!LOAD_BITMAP(sign04a))
		goto destroy;
	if (!LOAD_BITMAP(sign05))
		goto destroy;
	if (!LOAD_BITMAP(sign06))
		goto destroy;
	if (!LOAD_BITMAP(sign06a))
		goto destroy;
	if (!LOAD_BITMAP(sign07))
		goto destroy;
	if (!LOAD_BITMAP(sign08))
		goto destroy;
	if (!LOAD_BITMAP(sign09))
		goto destroy;
	if (!LOAD_BITMAP(sort_button_all))
		goto destroy;
	if (!LOAD_BITMAP(sort_button_combo))
		goto destroy;
	if (!LOAD_BITMAP(sort_button_floor))
		goto destroy;
	if (!LOAD_BITMAP(sort_button_name))
		goto destroy;
	if (!LOAD_BITMAP(sort_button_score))
		goto destroy;
	if (!LOAD_BITMAP(star01))
		goto destroy;
	if (!LOAD_BITMAP(star02))
		goto destroy;
	if (!LOAD_BITMAP(star03))
		goto destroy;
	if (!LOAD_BITMAP(star04))
		goto destroy;
	if (!LOAD_BITMAP(star05))
		goto destroy;
	if (!LOAD_BITMAP(star06))
		goto destroy;
	if (!LOAD_BITMAP(star07))
		goto destroy;
	if (!LOAD_BITMAP(star08))
		goto destroy;
	if (!LOAD_BITMAP(title))
		goto destroy;
	if (!LOAD_BITMAP(title_bg))
		goto destroy;
	if (!LOAD_BITMAP(vcr))
		goto destroy;
	if (!LOAD_BITMAP(vcr_left))
		goto destroy;
	if (!LOAD_BITMAP(vcr_right))
		goto destroy;
	if (!LOAD_BITMAP(vcr_up))
		goto destroy;

	if (!LOAD_BITMAP_CHARACTER(harold, chock))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, edge1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, edge2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, idle1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, idle2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, idle3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, jump))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, jump1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, jump2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, jump3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, rotate))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, walk1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, walk2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, walk3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(harold, walk4))
		goto destroy;

	if (!LOAD_BITMAP_CHARACTER(disco_dave, chock))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, edge1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, edge2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, idle1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, idle2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, idle3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, jump))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, jump1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, jump2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, jump3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, rotate))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, walk1))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, walk2))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, walk3))
		goto destroy;
	if (!LOAD_BITMAP_CHARACTER(disco_dave, walk4))
		goto destroy;

	return true;
destroy:
	gfx_destroy_bitmaps();
	return false;
}

void gfx_destroy_bitmaps(void) {
	DESTROY_BITMAP(bgtile);
	DESTROY_BITMAP(browse_button);
	DESTROY_BITMAP(bt_no);
	DESTROY_BITMAP(bt_yes);
	DESTROY_BITMAP(clock);
	DESTROY_BITMAP(clock_hand);
	DESTROY_BITMAP(combo_count);
	DESTROY_BITMAP(combo_liquid);
	DESTROY_BITMAP(combo_meter);
	DESTROY_BITMAP(floor01);
	DESTROY_BITMAP(floor02);
	DESTROY_BITMAP(floor03);
	DESTROY_BITMAP(floor04);
	DESTROY_BITMAP(floor05);
	DESTROY_BITMAP(floor06);
	DESTROY_BITMAP(floor07);
	DESTROY_BITMAP(floor08);
	DESTROY_BITMAP(floor09);
	DESTROY_BITMAP(floor10);
	DESTROY_BITMAP(floor11);
	DESTROY_BITMAP(floor12);
	DESTROY_BITMAP(floor12a);
	DESTROY_BITMAP(floor12b);
	DESTROY_BITMAP(floor12c);
	DESTROY_BITMAP(floor13);
	DESTROY_BITMAP(floor14);
	DESTROY_BITMAP(floor15);
	DESTROY_BITMAP(floor16);
	DESTROY_BITMAP(floor17);
	DESTROY_BITMAP(floor18);
	DESTROY_BITMAP(floor18a);
	DESTROY_BITMAP(floor18b);
	DESTROY_BITMAP(floor18c);
	DESTROY_BITMAP(floor19);
	DESTROY_BITMAP(floor20);
	DESTROY_BITMAP(floor21);
	DESTROY_BITMAP(floor22);
	DESTROY_BITMAP(floor23);
	DESTROY_BITMAP(floor24);
	DESTROY_BITMAP(floor25);
	DESTROY_BITMAP(floor26);
	DESTROY_BITMAP(floor27);
	DESTROY_BITMAP(gameover);
	DESTROY_BITMAP(heroface000);
	DESTROY_BITMAP(heroface001);
	DESTROY_BITMAP(heroface002);
	DESTROY_BITMAP(highscore);
	DESTROY_BITMAP(hint);
	DESTROY_BITMAP(hisctop);
	DESTROY_BITMAP(hurryup);
	DESTROY_BITMAP(instructions);
	DESTROY_BITMAP(menu_bullet);
	DESTROY_BITMAP(replay_bg);
	DESTROY_BITMAP(replay_buttons);
	DESTROY_BITMAP(reward000);
	DESTROY_BITMAP(reward001);
	DESTROY_BITMAP(reward002);
	DESTROY_BITMAP(reward003);
	DESTROY_BITMAP(reward004);
	DESTROY_BITMAP(reward005);
	DESTROY_BITMAP(reward006);
	DESTROY_BITMAP(reward007);
	DESTROY_BITMAP(reward008);
	DESTROY_BITMAP(reward009);
	DESTROY_BITMAP(sideblock);
	DESTROY_BITMAP(sign01);
	DESTROY_BITMAP(sign02);
	DESTROY_BITMAP(sign03);
	DESTROY_BITMAP(sign04);
	DESTROY_BITMAP(sign04a);
	DESTROY_BITMAP(sign05);
	DESTROY_BITMAP(sign06);
	DESTROY_BITMAP(sign06a);
	DESTROY_BITMAP(sign07);
	DESTROY_BITMAP(sign08);
	DESTROY_BITMAP(sign09);
	DESTROY_BITMAP(sort_button_all);
	DESTROY_BITMAP(sort_button_combo);
	DESTROY_BITMAP(sort_button_floor);
	DESTROY_BITMAP(sort_button_name);
	DESTROY_BITMAP(sort_button_score);
	DESTROY_BITMAP(star01);
	DESTROY_BITMAP(star02);
	DESTROY_BITMAP(star03);
	DESTROY_BITMAP(star04);
	DESTROY_BITMAP(star05);
	DESTROY_BITMAP(star06);
	DESTROY_BITMAP(star07);
	DESTROY_BITMAP(star08);
	DESTROY_BITMAP(title);
	DESTROY_BITMAP(title_bg);
	DESTROY_BITMAP(vcr);
	DESTROY_BITMAP(vcr_left);
	DESTROY_BITMAP(vcr_right);
	DESTROY_BITMAP(vcr_up);

	DESTROY_BITMAP_CHARACTER(harold, chock);
	DESTROY_BITMAP_CHARACTER(harold, edge1);
	DESTROY_BITMAP_CHARACTER(harold, edge2);
	DESTROY_BITMAP_CHARACTER(harold, idle1);
	DESTROY_BITMAP_CHARACTER(harold, idle2);
	DESTROY_BITMAP_CHARACTER(harold, idle3);
	DESTROY_BITMAP_CHARACTER(harold, jump);
	DESTROY_BITMAP_CHARACTER(harold, jump1);
	DESTROY_BITMAP_CHARACTER(harold, jump2);
	DESTROY_BITMAP_CHARACTER(harold, jump3);
	DESTROY_BITMAP_CHARACTER(harold, rotate);
	DESTROY_BITMAP_CHARACTER(harold, walk1);
	DESTROY_BITMAP_CHARACTER(harold, walk2);
	DESTROY_BITMAP_CHARACTER(harold, walk3);
	DESTROY_BITMAP_CHARACTER(harold, walk4);

	DESTROY_BITMAP_CHARACTER(disco_dave, chock);
	DESTROY_BITMAP_CHARACTER(disco_dave, edge1);
	DESTROY_BITMAP_CHARACTER(disco_dave, edge2);
	DESTROY_BITMAP_CHARACTER(disco_dave, idle1);
	DESTROY_BITMAP_CHARACTER(disco_dave, idle2);
	DESTROY_BITMAP_CHARACTER(disco_dave, idle3);
	DESTROY_BITMAP_CHARACTER(disco_dave, jump);
	DESTROY_BITMAP_CHARACTER(disco_dave, jump1);
	DESTROY_BITMAP_CHARACTER(disco_dave, jump2);
	DESTROY_BITMAP_CHARACTER(disco_dave, jump3);
	DESTROY_BITMAP_CHARACTER(disco_dave, rotate);
	DESTROY_BITMAP_CHARACTER(disco_dave, walk1);
	DESTROY_BITMAP_CHARACTER(disco_dave, walk2);
	DESTROY_BITMAP_CHARACTER(disco_dave, walk3);
	DESTROY_BITMAP_CHARACTER(disco_dave, walk4);
}

ALLEGRO_FONT *font_color;
ALLEGRO_FONT *font_mono;
ALLEGRO_FONT *font_native;

ALLEGRO_FONT *load_font(const char *directory, unsigned int first, unsigned int last) {
	unsigned int size = last - first + 1;
	ALLEGRO_BITMAP *bitmaps[size];
	ALLEGRO_COLOR background_color = al_map_rgb(1, 1, 1);
	unsigned int width = 0, height = 0, x, y;
	ALLEGRO_BITMAP *bitmap, *original_target;
	const int range[2] = {first, last};
	ALLEGRO_FONT *font;
	char *filename = malloc(strlen(directory) + sizeof "00000000.bmp");
	unsigned int i;

	for (i = 0; i < size; ++i) {
		sprintf(filename, "%s%.8x.bmp", directory, first + i);
		bitmaps[i] = al_load_bitmap(filename);
	}
	free(filename);

	for (i = 0; i < size; ++i) {
		if (bitmaps[i] == NULL)
			goto destroy;
	}

	for (i = 0; i < size; ++i) {
		width += al_get_bitmap_width(bitmaps[i]);
		if (al_get_bitmap_height(bitmaps[i]) > height) {
			height = al_get_bitmap_height(bitmaps[i]);
		}
	}
	width += size + 1;
	height += 2;

	bitmap = al_create_bitmap(width, height);
	original_target = al_get_target_bitmap();
	al_set_target_bitmap(bitmap);
	al_clear_to_color(MASK_COLOR);
	al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	for (y = 0; y < height; ++y)
		al_put_pixel(0, y, background_color);
	x = 1;
	for (i = 0; i < size; ++i) {
		for (y = x; y < x + al_get_bitmap_width(bitmaps[i]); ++y) {
			al_put_pixel(y, 0, background_color);
			al_put_pixel(y, height - 1, background_color);
		}
		x += al_get_bitmap_width(bitmaps[i]);
		for (y = 0; y < height; ++y)
			al_put_pixel(x, y, background_color);
		x += 1;
	}
	al_unlock_bitmap(bitmap);
	x = 1;
	for (i = 0; i < size; ++i) {
		al_draw_bitmap(bitmaps[i], x, 1, 0);
		x += al_get_bitmap_width(bitmaps[i]) + 1;
		al_destroy_bitmap(bitmaps[i]);
	}
	al_set_target_bitmap(original_target);
	al_convert_mask_to_alpha(bitmap, MASK_COLOR);
	font = al_grab_font_from_bitmap(bitmap, 1, range);
	al_destroy_bitmap(bitmap);
	return font;

destroy:
	for (i = 0; i < size; ++i)
		al_destroy_bitmap(bitmaps[i]);
	return NULL;
}

bool gfx_load_fonts(void) {
	font_color = load_font("gfx/font1/", 0x20, 0x7f);
	font_mono = load_font("gfx/font2/", 0x20, 0x7f);
	font_native = load_font("gfx/font3/", 0x20, 0x7f);
	if (!font_color || !font_mono || !font_native) {
		gfx_destroy_fonts();
		return false;
	}
	return true;
}

#define DESTROY_FONT(font) do {\
	al_destroy_font(font);\
	font = NULL;\
} while (false)

void gfx_destroy_fonts(void) {
	DESTROY_FONT(font_color);
	DESTROY_FONT(font_mono);
	DESTROY_FONT(font_native);
}
