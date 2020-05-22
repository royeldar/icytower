#include <allegro5/allegro.h>

#include "options.h"

unsigned int character_index = 0;
unsigned int start_floor = 0;
unsigned int eye_candy = 0;
bool fullscreen = false;
unsigned int volume_sfx = 10, volume_music = 10;
int key_left = ALLEGRO_KEY_LEFT;
int key_right = ALLEGRO_KEY_RIGHT;
int key_jump = ALLEGRO_KEY_SPACE;
int key_pause = ALLEGRO_KEY_P;
bool rejump = true;
