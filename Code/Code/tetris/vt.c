#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include "keyboard/keyboard.h"

#define W 10
#define H 20
#define BC 0
#define FC 5

struct data{
	int x;
	int y;
};

struct shape {
	int s[5][5];
};

int backgroud[H][W] = {};
struct shape  shap_arr[7] = {
	{ 0,0,0,0,0, 0,1,1,1,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0 }
};

int idx = 0;

void set_back(struct data *t, struct shape p)
{
	int i;
	int j;
	
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			if ( p.s[i][j] != 0 )
				backgroud[t->y+i][t->x+j] = 1;
		}
	}
}

void drap_element(int x, int y, int c)
{
	x = x*2;
	x++;
	y++;
	printf("\033[%d;%dH\033[3%dm\033[4%dm[]", y, x, c, c);
	printf("\033[?25l");
	printf("\033[0m");
	fflush(stdout);
}

void draw_back()
{
	int i = 0;
	int j = 0;
	
	for (i=0; i<H; i++) {
		for (j=0; j<W; j++) {
			if ( backgroud[i][j] == 0 )
				drap_element(j, i, BC);
			else
				drap_element(j, i, FC);
		}
	}
}

void draw_shape(int x, int y, struct shape p, int c)
{
	int i;
	int j;
	
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			if ( p.s[i][j] != 0 )
				drap_element(x+j, y+i, c);
		}
	}
}

int can_move(int x, int y, struct shape p)
{
	int i;
	int j;
	
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			if ( p.s[i][j] == 0 )
				continue;
			if ( x+j >= W )
				return 0;
			if ( x+j < 0 )
				return 0;
			if ( y+i >= H )
				return 0;
			if ( backgroud[y+i][x+j] != 0 )
				return 0;
		}
	}
	
	return 1;
}

void mclean_line()
{
	int i;
	int j;
	int k;
	int total;
	
	for (i=0; i<H; i++) {
		total = 0;
		for (j=0; j<W; j++) {
			if ( backgroud[i][j] != 0 )
				total++;
		}
		if ( total == W ) {
			for ( k = i; k>=1; k--)
				memcpy(backgroud[k],backgroud[k-1],sizeof(backgroud[k]));
			memset(backgroud[0], 0x00, sizeof(backgroud[0]));
		}
	}
}

void tetris_timer( struct data *t)
{
	draw_shape(t->x, t->y, shap_arr[idx], BC);
	if ( can_move(t->x, t->y+1, shap_arr[idx]) ) {
		t->y++;
		draw_shape(t->x, t->y, shap_arr[idx], FC);
	} else {
		set_back(t, shap_arr[idx]);
		mclean_line();
		draw_back();
		t->x = 1;
		t->y = 0;
		idx = rand() % 7;
		draw_shape(t->x, t->y, shap_arr[idx], FC);
	}
}

struct shape turn_90(struct shape p)
{
	int i;
	int j;
	struct shape tmp;
	
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			tmp.s[i][j] = p.s[4-j][i];
		}
	}

	return tmp;
}

void tetris(struct data *t)
{
	int c = get_key();
	
	if ( is_up(c) ) {
		draw_shape(t->x, t->y, shap_arr[idx], BC);
		shap_arr[idx] = turn_90(shap_arr[idx]);
		if ( can_move(t->x, t->y, shap_arr[idx]) == 0 ) {
			shap_arr[idx] = turn_90(shap_arr[idx]);
			shap_arr[idx] = turn_90(shap_arr[idx]);
			shap_arr[idx] = turn_90(shap_arr[idx]);
		}
		draw_shape(t->x, t->y, shap_arr[idx], FC);
	} else if ( is_down(c) ) {
		draw_shape(t->x, t->y, shap_arr[idx], BC);
		if ( can_move(t->x, t->y+1, shap_arr[idx]) ) {
			t->y++;
			draw_shape(t->x, t->y, shap_arr[idx], FC);
		} else {
			draw_shape(t->x, t->y, shap_arr[idx], BC);
		}
	} else if ( is_left(c) ) {
		draw_shape(t->x, t->y, shap_arr[idx], BC);
		if ( can_move(t->x-1, t->y, shap_arr[idx]) ) {
			t->x--;
			draw_shape(t->x, t->y, shap_arr[idx], FC);
		} else {
			draw_shape(t->x, t->y, shap_arr[idx], BC);
		}
	} else if ( is_right(c) ) {
		draw_shape(t->x, t->y, shap_arr[idx], BC);
		if ( can_move(t->x+1, t->y, shap_arr[idx]) ) {
			t->x++;
			draw_shape(t->x, t->y, shap_arr[idx], FC);
		} else {
			draw_shape(t->x, t->y, shap_arr[idx], BC);
		}
	}
}

struct data t = {.x=5, .y=0};
void handler(int s)
{
	tetris_timer(&t); // 控制方块下落
	tetris(&t);
}

int main( void )
{
	srand(time(NULL));
	draw_back();
	init_keyboard();
	
	idx = rand() % 7;
	
	struct itimerval vi;
	vi.it_interval.tv_sec  = 0;
	vi.it_interval.tv_usec = 500000;
	vi.it_value.tv_sec  = 0;
	vi.it_value.tv_usec = 1;
	
	signal(SIGALRM, handler);
	if ( setitimer(ITIMER_REAL, &vi, NULL) == -1 )
		exit(0);
	
	while ( 1 ) {
		pause();
	}
	
	recover_keyboard();
}

