#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

#include "icytower.h"
#include "gfx.h"
#include "sfx.h"
#include "menu.h"
#include "options.h"
#include "characters.h"
#include "floor_types.h"
#include "game.h"

bool initialize(void) {
	if (!al_init()) {
		printf("Failed to initialize the Allegro system\n");
		return false;
	}
	if (!al_init_image_addon()) {
		printf("Failed to initialize the image i/o addon\n");
		return false;
	}
	if (!al_init_font_addon()) {
		printf("Failed to initialize the font addons\n");
		return false;
	}
	if (!al_install_keyboard()) {
		printf("Failed to install the keyboard driver\n");
		return false;
	}
	if (!al_install_audio()) {
		printf("Failed to install the audio subsystem\n");
		return false;
	}
	if (!al_init_acodec_addon()) {
		printf("Failed to initialize the audio codecs\n");
		return false;
	}
	if (!al_reserve_samples(16)) {
		printf("Failed to reserve audio sample instances\n");
		return false;
	}
	return true;
}

void initialize_music(ALLEGRO_AUDIO_STREAM *audio_stream) {
	al_set_audio_stream_playing(audio_stream, false);
	al_set_audio_stream_playmode(audio_stream, ALLEGRO_PLAYMODE_LOOP);
	al_attach_audio_stream_to_mixer(audio_stream, al_get_default_mixer());
}

void play_music(ALLEGRO_AUDIO_STREAM *audio_stream) {
	al_rewind_audio_stream(audio_stream);
	al_set_audio_stream_playing(audio_stream, true);
}

void stop_music(ALLEGRO_AUDIO_STREAM *audio_stream) {
	al_set_audio_stream_playing(audio_stream, false);
}

void start_game(void) {
	stop_music(audio_stream_bg_menu);
	play_music(characters[character_index].sfx.bgmusic);
	initialize_game();
	draw_game();
	al_play_sample(characters[character_index].sfx.greeting, volume_sfx / 10.0,
			0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void pause_game(void) {
	al_play_sample(characters[character_index].sfx.pause, volume_sfx / 10.0,
			0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void main_menu(void) {
	stop_music(characters[character_index].sfx.bgmusic);
	play_music(audio_stream_bg_menu);
}

enum GAME_STATE game_state;

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT event;
	bool redraw;
	bool game_running;

	if (!initialize())
		goto cleanup;

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(640, 480);
	if (display == NULL) {
		printf("Failed to create a display\n");
		goto cleanup;
	}

	timer = al_create_timer(1.0 / 50.0);
	if (timer == NULL) {
		printf("Failed to create a timer\n");
		goto cleanup;
	}

	event_queue = al_create_event_queue();
	if (event_queue == NULL) {
		printf("Failed to create an event queue\n");
		goto cleanup;
	}

	al_register_event_source(event_queue,
			al_get_keyboard_event_source());
	al_register_event_source(event_queue,
			al_get_display_event_source(display));
	al_register_event_source(event_queue,
			al_get_timer_event_source(timer));

	printf("Loading gfx resources...\n");
	if (!gfx_load_bitmaps()) {
		printf("Failed to load gfx resources\n");
		goto cleanup;
	}
	printf("Loading fonts...\n");
	if (!gfx_load_fonts()) {
		printf("Failed to load fonts\n");
		goto cleanup;
	}
	printf("Loading sfx resources...\n");
	if (!sfx_load_audio_streams_and_samples()) {
		printf("Failed to load sfx resources\n");
		goto cleanup;
	}

	initialize_characters();
	initialize_floor_types();

	initialize_music(audio_stream_bg_beat);
	initialize_music(audio_stream_disco_dave_bg_dave);
	initialize_music(audio_stream_bg_menu);

	game_state = TITLE;
	main_menu();

	game_running = true;
	redraw = true;
	al_start_timer(timer);
	while (game_running) {
		al_wait_for_event(event_queue, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			goto cleanup;
		case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
			al_acknowledge_drawing_halt(display);
			al_stop_timer(timer);
			break;
		case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
			al_acknowledge_drawing_resume(display);
			al_resume_timer(timer);
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
			/* pause the game */
			break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
			/* resume the game */
			break;
		case ALLEGRO_EVENT_TIMER:
			switch (game_state) {
			case TITLE:
				draw_menu();
				break;
			case INSTRUCTIONS:
				draw_instructions();
				break;
			case PLAYING:
				do_tick();
				draw_game();
				break;
			case EXIT:
				game_running = false;
				break;
			}
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (game_state) {
			case TITLE:
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					menu_up();
					break;
				case ALLEGRO_KEY_DOWN:
					menu_down();
					break;
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
					menu_enter();
					break;
				case ALLEGRO_KEY_ESCAPE:
					menu_escape();
					break;
				case ALLEGRO_KEY_LEFT:
					menu_left();
					break;
				case ALLEGRO_KEY_RIGHT:
					menu_right();
					break;
				}
				break;
			case INSTRUCTIONS:
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
				case ALLEGRO_KEY_SPACE:
				case ALLEGRO_KEY_ESCAPE:
					game_state = TITLE;
					break;
				}
				break;
			case PLAYING:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					game_state = ESCAPE;
					pause_game();
				} else if (event.keyboard.keycode == key_pause) {
					game_state = PAUSE;
					pause_game();
				} else if (event.keyboard.keycode == key_left)
					press_left();
				else if (event.keyboard.keycode == key_right)
					press_right();
				else if (event.keyboard.keycode == key_jump)
					press_jump();
				break;
			case PAUSE:
				game_state = PLAYING;
				break;
			case ESCAPE:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					al_play_sample(sample_tryagain, volume_sfx / 10.0,
							0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					game_state = TITLE;
					main_menu();
				} else {
					game_state = PLAYING;
				}
				break;
			case EXIT:
				break;
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (game_state == PLAYING) {
				if (event.keyboard.keycode == key_left)
					release_left();
				else if (event.keyboard.keycode == key_right)
					release_right();
				else if (event.keyboard.keycode == key_jump)
					release_jump();
			}
			break;
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			al_flip_display();
			redraw = false;
		}
	}

cleanup:
	sfx_destroy_audio_streams_and_samples();
	gfx_destroy_fonts();
	gfx_destroy_bitmaps();

	if (event_queue)
		al_destroy_event_queue(event_queue);
	if (timer)
		al_destroy_timer(timer);
	if (display)
		al_destroy_display(display);
	return 0;
}
