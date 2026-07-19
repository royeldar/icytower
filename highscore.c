#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "highscore.h"

static int compare_players(const void *a, const void *b) {
	return strcmp(((const PLAYER_DATA *)a)->name,
	              ((const PLAYER_DATA *)b)->name);
}

HIGHSCORE_LIST hs_score;
HIGHSCORE_LIST hs_floor;
HIGHSCORE_LIST hs_combo;

PLAYER_DATA players[MAX_PLAYERS];
unsigned int player_count = 0;
char hs_last_name[3] = "AA";

/* ---- global list (value name date) ---- */

static void load_list(HIGHSCORE_LIST *list, const char *filename) {
	list->count = 0;
	FILE *f = fopen(filename, "r");
	if (!f) return;
	while (list->count < HIGHSCORE_COUNT) {
		HIGHSCORE_ENTRY *e = &list->entries[list->count];
		long long date;
		if (fscanf(f, "%u %2s %lld", &e->value, e->name, &date) != 3)
			break;
		e->name[2] = '\0';
		e->date = (time_t)date;
		list->count++;
	}
	fclose(f);
}

static void save_list(HIGHSCORE_LIST *list, const char *filename) {
	FILE *f = fopen(filename, "w");
	if (!f) return;
	for (unsigned int i = 0; i < list->count; i++)
		fprintf(f, "%u %s %lld\n", list->entries[i].value,
				list->entries[i].name,
				(long long)list->entries[i].date);
	fclose(f);
}

/* ---- per-player list (value date, no name) ---- */

static void load_player_list(HIGHSCORE_LIST *list, FILE *f) {
	list->count = 0;
	while (list->count < HIGHSCORE_COUNT) {
		HIGHSCORE_ENTRY *e = &list->entries[list->count];
		long long date;
		if (fscanf(f, " %u %lld", &e->value, &date) != 2)
			break;
		/* peek: stop if next token is a section header */
		e->date = (time_t)date;
		e->name[0] = '\0';
		list->count++;
	}
}

static void save_player_list(HIGHSCORE_LIST *list, FILE *f) {
	for (unsigned int i = 0; i < list->count; i++)
		fprintf(f, "%u %lld\n", list->entries[i].value,
				(long long)list->entries[i].date);
}

static void load_player(PLAYER_DATA *p) {
	char filename[32];
	snprintf(filename, sizeof filename, "player_%s.txt", p->name);
	FILE *f = fopen(filename, "r");
	if (!f) return;
	char section[16];
	while (fscanf(f, " [%15[^]]]", section) == 1) {
		if (strcmp(section, "score") == 0)
			load_player_list(&p->score, f);
		else if (strcmp(section, "floor") == 0)
			load_player_list(&p->floor, f);
		else if (strcmp(section, "combo") == 0)
			load_player_list(&p->combo, f);
	}
	fclose(f);
}

void highscore_save_player(PLAYER_DATA *p) {
	char filename[32];
	snprintf(filename, sizeof filename, "player_%s.txt", p->name);
	FILE *f = fopen(filename, "w");
	if (!f) return;
	fprintf(f, "[score]\n"); save_player_list(&p->score, f);
	fprintf(f, "[floor]\n"); save_player_list(&p->floor, f);
	fprintf(f, "[combo]\n"); save_player_list(&p->combo, f);
	fclose(f);
}

/* ---- load / save ---- */

void highscore_load(void) {
	load_list(&hs_score, "hs_score.txt");
	load_list(&hs_floor, "hs_floor.txt");
	load_list(&hs_combo, "hs_combo.txt");

	player_count = 0;
	FILE *f = fopen("players.txt", "r");
	if (!f) return;
	while (player_count < MAX_PLAYERS) {
		char name[3];
		if (fscanf(f, " %2s", name) != 1) break;
		name[2] = '\0';
		memcpy(players[player_count].name, name, 3);
		players[player_count].score.count = 0;
		players[player_count].floor.count = 0;
		players[player_count].combo.count = 0;
		load_player(&players[player_count]);
		player_count++;
	}
	fclose(f);
	qsort(players, player_count, sizeof(PLAYER_DATA), compare_players);

	FILE *lf = fopen("last_player.txt", "r");
	if (lf) {
		char name[3];
		if (fscanf(lf, " %2s", name) == 1) {
			name[2] = '\0';
			memcpy(hs_last_name, name, 3);
		}
		fclose(lf);
	}
}

void highscore_save_last_name(const char *name) {
	memcpy(hs_last_name, name, 3);
	FILE *f = fopen("last_player.txt", "w");
	if (f) { fprintf(f, "%s\n", name); fclose(f); }
}

void highscore_save(void) {
	save_list(&hs_score, "hs_score.txt");
	save_list(&hs_floor, "hs_floor.txt");
	save_list(&hs_combo, "hs_combo.txt");
}

/* ---- submit ---- */

int highscore_submit(HIGHSCORE_LIST *list, unsigned int value) {
	unsigned int rank;
	for (rank = 0; rank < list->count; rank++)
		if (value > list->entries[rank].value)
			break;
	if (rank >= HIGHSCORE_COUNT)
		return 0;
	unsigned int new_count = list->count < HIGHSCORE_COUNT
			? list->count + 1 : HIGHSCORE_COUNT;
	for (unsigned int i = new_count - 1; i > rank; i--)
		list->entries[i] = list->entries[i - 1];
	list->entries[rank].value = value;
	list->entries[rank].name[0] = '?';
	list->entries[rank].name[1] = '?';
	list->entries[rank].name[2] = '\0';
	list->entries[rank].date = time(NULL);
	list->count = new_count;
	return (int)rank + 1;
}

int highscore_submit_personal(HIGHSCORE_LIST *list, unsigned int value) {
	unsigned int rank;
	for (rank = 0; rank < list->count; rank++)
		if (value > list->entries[rank].value)
			break;
	if (rank >= HIGHSCORE_COUNT)
		return 0;
	unsigned int new_count = list->count < HIGHSCORE_COUNT
			? list->count + 1 : HIGHSCORE_COUNT;
	for (unsigned int i = new_count - 1; i > rank; i--)
		list->entries[i] = list->entries[i - 1];
	list->entries[rank].value = value;
	list->entries[rank].name[0] = '\0';
	list->entries[rank].date = time(NULL);
	list->count = new_count;
	return (int)rank + 1;
}

PLAYER_DATA *highscore_find_or_create_player(const char *name) {
	for (unsigned int i = 0; i < player_count; i++)
		if (strcmp(players[i].name, name) == 0)
			return &players[i];
	if (player_count >= MAX_PLAYERS)
		return NULL;
	memcpy(players[player_count].name, name, 3);
	players[player_count].score.count = 0;
	players[player_count].floor.count = 0;
	players[player_count].combo.count = 0;
	/* register in index file */
	FILE *f = fopen("players.txt", "a");
	if (f) { fprintf(f, "%s\n", name); fclose(f); }
	player_count++;
	qsort(players, player_count, sizeof(PLAYER_DATA), compare_players);
	/* return pointer to sorted position */
	for (unsigned int i = 0; i < player_count; i++)
		if (strcmp(players[i].name, name) == 0)
			return &players[i];
	return NULL; /* unreachable */
}
