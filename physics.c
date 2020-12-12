#include "physics.h"

void init_state(IT_STATE *its, int rejump, unsigned int seed)
{
	int i;

	its->x = 200;
	its->y = 431;
	its->dx = 0.000833333353511989116668701171875;
	its->dy = 0;

	its->status = STATUS_IDLE;
	its->screen_y = 0;

	its->speed = its->speed_counter = its->zero_speed_skip = 0;

	its->rejump = rejump;
	its->rejump_jumped = 0;

	its->combo_timer = its->combo_count = its->combo_floor = 0;
	its->score = its->floor = its->combo = 0;

	its->floors.start = 0;
	its->floors.count = 0;
	its->floors.pad = 2;
	its->floors.seed = seed;

	for(i=0; i<32; i++)
		new_floor(&its->floors);
}

int play_frame(IT_STATE *its, int keys)
{
	int prev_x, prev_y;
	int screen_move;

	prev_x = FTOI(its->x);
	prev_y = FTOI(its->y);

	handle_keys(its, keys);
	handle_pos(its);

	if(its->y < 160)
	{
		if(its->y < 0)
			screen_move = 13;
		else if(its->y < 20)
			screen_move = 10;
		else if(its->y < 40)
			screen_move = 8;
		else if(its->y < 60)
			screen_move = 6;
		else if(its->y < 80)
			screen_move = 5;
		else if(its->y < 100)
			screen_move = 4;
		else if(its->y < 120)
			screen_move = 3;
		else if(its->y < 140)
			screen_move = 2;
		else
			screen_move = 1;
	}
	else
		screen_move = 0;

	if(its->screen_y+screen_move > 100)
	{
		if(its->speed > 0)
			screen_move += its->speed;
		else if(!its->zero_speed_skip)
			screen_move++;

		if(its->speed < 5)
		{
			its->speed_counter++;
			if(its->speed_counter > 1800)
			{
				its->speed++;
				its->speed_counter -= 1800;
			}
		}
	}

	its->zero_speed_skip = !its->zero_speed_skip;

	if(screen_move)
	{
		its->screen_y += screen_move;
		its->y += screen_move;
		prev_y += screen_move;

		if(its->screen_y%16 < (its->screen_y-screen_move)%16 || screen_move >= 16)
			new_floor(&its->floors);
	}

	if(its->combo_timer)
	{
		its->combo_timer--;
		if(its->combo_timer == 0 && its->combo_count > 1)
		{
			its->score += its->combo_floor*its->combo_floor;
			if(its->combo_floor > its->combo)
				its->combo = its->combo_floor;
		}
	}

	handle_collision(its, prev_x, prev_y);

	return its->y <= 540;
}

void handle_keys(IT_STATE *its, int keys)
{
	if(keys & KEY_LEFT)
	{
		if(its->dx > 0)
			its->dx *= 0.74287378787994384765625;

		its->dx -= 0.25;
	}
	else if(keys & KEY_RIGHT)
	{
		if(its->dx < 0)
			its->dx *= 0.74287378787994384765625;

		its->dx += 0.25;
	}
	else
		its->dx *= 0.915943682193756103515625;

	if(its->rejump)
	{
		if(keys & KEY_JUMP)
			jump(its);
	}
	else
	{
		if(keys & KEY_JUMP)
		{
			if(!its->rejump_jumped && jump(its))
				its->rejump_jumped = 1;
		}
		else
			its->rejump_jumped = 0;
	}
}

int jump(IT_STATE *its)
{
	if(its->status != STATUS_IDLE)
		return 0;

	its->status = STATUS_FLY_UP;

	its->dy = its->dx*2;

	if(its->dy > 0)
		its->dy = -its->dy;

	if(its->dy > -10.16666698455810546875)
		its->dy = -10.16666698455810546875;

	return 1;
}

void handle_pos(IT_STATE *its)
{
	if(its->dx > 10.16666698455810546875)
		its->dx = 10.16666698455810546875;
	else if(its->dx < -10.16666698455810546875)
		its->dx = -10.16666698455810546875;

	if(its->dy > 10.16666698455810546875)
		its->dy = 10.16666698455810546875;
	else if(its->dy < -83.33333587646484375) // yea that's useless
		its->dy = -83.33333587646484375;

	its->x += its->dx;
	if(its->x > 555)
	{
		its->x = 555;
		its->dx *= -0.915943682193756103515625;
	}
	else if(its->x < 85)
	{
		its->x = 85;
		its->dx *= -0.915943682193756103515625;
	}

	its->y += its->dy;
	if(its->y > 1000) // that's useless too
		its->y = 1000;

	if(its->status != STATUS_IDLE)
	{
		its->dy += 0.666666686534881591796875;
		if(its->status == STATUS_FLY_UP && its->dy>0)
			its->status = STATUS_FLY_IDLE;
	}
}

void new_floor(FLOORS *floors)
{
	int length;

	if(floors->pad < 4)
	{
		floors->pad++;
		return;
	}

	floors->pad = 0;

	if(floors->count<=1000 ? !(floors->count%50) : !(floors->count%500))
	{
		floors->floor[floors->start].start = 0;
		floors->floor[floors->start].end = 40;
	}
	else
	{
		if(floors->count < 240)
			length = 6 + rand_p(&floors->seed)%(9-floors->count/30);
		else if(floors->count < 600)
		{
			length = 6;
			rand_p(&floors->seed);
		}
		else if(floors->count < 1000)
			length = 6;
		else if(floors->count < 1500)
			length = 5;
		else if(floors->count < 2000)
			length = 4;
		else if(floors->count < 10000)
			length = 3;
		else
			length = 2;

		floors->floor[floors->start].start = 5 + rand_p(&floors->seed)%(30-length);
		floors->floor[floors->start].end = floors->floor[floors->start].start + length;
	}

	floors->start++;
	if(floors->start == 7)
		floors->start = 0;

	floors->count++;
}

int rand_p(unsigned int *seed)
{
	// A "portable" version of the rand function, where the seed
	// is a parameter, and not an internal variable

	return ((*seed = *seed * 214013 + 2531011) >> 16) & 0x7FFF;
}

void handle_collision(IT_STATE *its, int prev_x, int prev_y)
{
	int floor_y, floor_xl, floor_xr, floor_level;
	int col_x1, col_y1, col_x2, col_y2;
	int check_1, check_2;

	if(its->status == STATUS_FLY_UP)
		return;

	if(
		!floor_from_y(&its->floors, FTOI(its->y), its->screen_y, &floor_y, &floor_xl, &floor_xr, &floor_level) && 
		!floor_from_y(&its->floors, prev_y, its->screen_y, &floor_y, &floor_xl, &floor_xr, &floor_level)
	)
	{
		if(its->status == STATUS_FLY_IDLE || its->status == STATUS_IDLE)
			its->status = STATUS_FLY_DOWN;

		return;
	}

	check_1 = line_intersection(floor_xl, floor_y, floor_xr, floor_y, 
		FTOI(its->x)-11, FTOI(its->y)+1, prev_x-11, prev_y, &col_x1, &col_y1);

	if(!check_1)
	{
		check_2 = line_intersection(floor_xl, floor_y, floor_xr, floor_y, 
			FTOI(its->x)+11, FTOI(its->y)+1, prev_x+11, prev_y, &col_x2, &col_y2);

		if(!check_2)
		{
			if(its->status == STATUS_FLY_IDLE || its->status == STATUS_IDLE)
				its->status = STATUS_FLY_DOWN;

			return;
		}
	}

	if(its->status == STATUS_FLY_IDLE || its->status == STATUS_FLY_DOWN)
	{
		its->status = STATUS_IDLE;
		its->y = floor_y-1;
		its->dy = 0;

		if(check_1)
			its->x = col_x1+11;
		else
			its->x = col_x2-11;

		if(floor_level-its->floor > 1)
		{
			if(its->combo_timer)
			{
				its->combo_floor += floor_level-its->floor;
				its->combo_count++;
			}
			else
			{
				its->combo_floor = floor_level-its->floor;
				its->combo_count = 1;
			}

			its->combo_timer = 120;
		}
		else if(floor_level != its->floor && its->combo_timer)
			its->combo_timer = 1;

		its->floor = floor_level;
	}
}

int floor_from_y(FLOORS *floors, int y, int screen_y, int *floor_y, int *floor_xl, int *floor_xr, int *floor_level)
{
	int y_relative;
	int floor, index;

	if(y < -33 || y > 478)
		return 0;

	y_relative = y+33+80-floors->pad*16;
	if(y_relative%80 > 15)
		return 0;

	floor = y_relative/80;
	index = floors->start - floor;
	if(index < 0)
		index += 7;

	*floor_y = (y+1) - (y+1)%16 + screen_y%16;
	*floor_xl = floors->floor[index].start*16 - 2;
	*floor_xr = (floors->floor[index].end+1)*16 + 1;
	*floor_level = floors->count - floor;

	return 1;
}

int line_intersection(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int *xi, int *yi)
{
	// http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/

	int denominator;
	double mul, ua, ub;

	denominator = (y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
	if(denominator == 0)
		return 0; // parallel or coincident

	mul = (double)1/denominator;

	ua = (double)((x4-x3)*(y1-y3)-(y4-y3)*(x1-x3)) * mul;
	if(ua<0 || ua>1)
		return 0;

	ub = (double)((x2-x1)*(y1-y3)-(y2-y1)*(x1-x3)) * mul;
	if(ub<0 || ub>1)
		return 0;

	*xi = x1 + FTOI(ua*(x2-x1) + 0.5);
	*yi = y1 + FTOI(ua*(y2-y1) + 0.5);

	return 1;
}
