#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <time.h>

#define HIGHSCORE_COUNT 15
#define MAX_PLAYERS     64

typedef struct {
	unsigned int value;
	char name[3];   /* only used in global lists */
	time_t date;
} HIGHSCORE_ENTRY;

typedef struct {
	HIGHSCORE_ENTRY entries[HIGHSCORE_COUNT];
	unsigned int count;
} HIGHSCORE_LIST;

/* Global top-15 across all players */
extern HIGHSCORE_LIST hs_score;
extern HIGHSCORE_LIST hs_floor;
extern HIGHSCORE_LIST hs_combo;

/* Per-player top-15 per category */
typedef struct {
	char name[3];
	HIGHSCORE_LIST score;
	HIGHSCORE_LIST floor;
	HIGHSCORE_LIST combo;
} PLAYER_DATA;

extern PLAYER_DATA players[MAX_PLAYERS];
extern unsigned int player_count;

extern char hs_last_name[3];

void highscore_load(void);
void highscore_save(void);

/* Submit to a global list; returns rank (1-based) or 0.
 * Name is left as "??" — caller must set it before saving. */
int highscore_submit(HIGHSCORE_LIST *list, unsigned int value);

/* Submit to a personal list (no name stored). */
int highscore_submit_personal(HIGHSCORE_LIST *list, unsigned int value);

/* Find existing player or create a new one. Returns NULL if MAX_PLAYERS reached. */
PLAYER_DATA *highscore_find_or_create_player(const char *name);

void highscore_save_player(PLAYER_DATA *player);
void highscore_save_last_name(const char *name);

#endif
