#include <allegro5/allegro.h>

struct floor_type {
	ALLEGRO_BITMAP *left;
	ALLEGRO_BITMAP *mid;
	ALLEGRO_BITMAP *right;
};

extern const struct floor_type *floor_types;
extern size_t floor_types_count;

void initialize_floor_types(void);
