#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <stdbool.h>

extern ALLEGRO_AUDIO_STREAM *audio_stream_bg_beat;
extern ALLEGRO_AUDIO_STREAM *audio_stream_bg_menu;

extern ALLEGRO_SAMPLE *sample_aight;
extern ALLEGRO_SAMPLE *sample_amazing;
extern ALLEGRO_SAMPLE *sample_cheer;
extern ALLEGRO_SAMPLE *sample_extreme;
extern ALLEGRO_SAMPLE *sample_fantastic;
extern ALLEGRO_SAMPLE *sample_gameover;
extern ALLEGRO_SAMPLE *sample_good;
extern ALLEGRO_SAMPLE *sample_great;
extern ALLEGRO_SAMPLE *sample_hurryup;
extern ALLEGRO_SAMPLE *sample_menu_change;
extern ALLEGRO_SAMPLE *sample_menu_choose;
extern ALLEGRO_SAMPLE *sample_ring;
extern ALLEGRO_SAMPLE *sample_splat;
extern ALLEGRO_SAMPLE *sample_splendid;
extern ALLEGRO_SAMPLE *sample_step;
extern ALLEGRO_SAMPLE *sample_super;
extern ALLEGRO_SAMPLE *sample_sweet;
extern ALLEGRO_SAMPLE *sample_tryagain;
extern ALLEGRO_SAMPLE *sample_unbelievable;
extern ALLEGRO_SAMPLE *sample_wow;

extern ALLEGRO_SAMPLE *sample_harold_edge;
extern ALLEGRO_SAMPLE *sample_harold_falling;
extern ALLEGRO_SAMPLE *sample_harold_jump_hi;
extern ALLEGRO_SAMPLE *sample_harold_jump_lo;
extern ALLEGRO_SAMPLE *sample_harold_jump_mid;
extern ALLEGRO_SAMPLE *sample_harold_wazup;
extern ALLEGRO_SAMPLE *sample_harold_yo;

extern ALLEGRO_AUDIO_STREAM *audio_stream_disco_dave_bg_dave;
extern ALLEGRO_SAMPLE *sample_disco_dave_ahey;
extern ALLEGRO_SAMPLE *sample_disco_dave_cmonyo;
extern ALLEGRO_SAMPLE *sample_disco_dave_diggin;
extern ALLEGRO_SAMPLE *sample_disco_dave_goinon;
extern ALLEGRO_SAMPLE *sample_disco_dave_ho;
extern ALLEGRO_SAMPLE *sample_disco_dave_stayinalive;
extern ALLEGRO_SAMPLE *sample_disco_dave_watchit;

bool sfx_load_audio_streams_and_samples(void);
void sfx_destroy_audio_streams_and_samples(void);
