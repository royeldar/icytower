#include <allegro5/allegro.h>

#include "floor_types.h"
#include "gfx.h"

const struct floor_type *floor_types;
size_t floor_types_count;

void initialize_floor_types(void) {
	static struct floor_type _floor_types[11];
	struct floor_type *stone = &_floor_types[0];
	struct floor_type *ice = &_floor_types[1];
	struct floor_type *wood = &_floor_types[2];
	struct floor_type *metal = &_floor_types[3];
	struct floor_type *gum = &_floor_types[4];
	struct floor_type *bone = &_floor_types[5];
	struct floor_type *vines = &_floor_types[6];
	struct floor_type *pipe = &_floor_types[7];
	struct floor_type *cloud = &_floor_types[8];
	struct floor_type *rainbow = &_floor_types[9];
	struct floor_type *glass = &_floor_types[10];
	floor_types = _floor_types;
	floor_types_count = sizeof(_floor_types) / sizeof(*_floor_types);
	
	stone->left = bitmap_floor01;
	stone->mid = bitmap_floor02;
	stone->right = bitmap_floor03;
	ice->left = bitmap_floor04;
	ice->mid = bitmap_floor05;
	ice->right = bitmap_floor06;
	wood->left = bitmap_floor07;
	wood->mid = bitmap_floor08;
	wood->right = bitmap_floor09;
	metal->left = bitmap_floor10;
	metal->mid = bitmap_floor11;
	metal->right = bitmap_floor12;
	gum->left = bitmap_floor12a;
	gum->mid = bitmap_floor12b;
	gum->right = bitmap_floor12c;
	bone->left = bitmap_floor13;
	bone->mid = bitmap_floor14;
	bone->right = bitmap_floor15;
	vines->left = bitmap_floor16;
	vines->mid = bitmap_floor17;
	vines->right = bitmap_floor18;
	pipe->left = bitmap_floor18a;
	pipe->mid = bitmap_floor18b;
	pipe->right = bitmap_floor18c;
	cloud->left = bitmap_floor19;
	cloud->mid = bitmap_floor20;
	cloud->right = bitmap_floor21;
	rainbow->left = bitmap_floor22;
	rainbow->mid = bitmap_floor23;
	rainbow->right = bitmap_floor24;
	glass->left = bitmap_floor25;
	glass->mid = bitmap_floor26;
	glass->right = bitmap_floor27;
}
