#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <CCORE.h>

#include "window.h"
#include "player.h"
#include "enemies.h"
#include "log.h"

#define MAX_FRAMES 		(20)
#define MILLIS_IN_FRAME 	(1000 / MAX_FRAMES)

static uint current_frame = 0;

static void _init(void)
{
	enemies_init();
	player_init();
}

int main() {
	int ch = 0;
	srand(time(NULL));   
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	log_info("Press any key to start\nUse arrow keys for moving\nUse SPACE for fire");

	_init();

	while (1) {
		clear();

		// processing
		current_frame++;
		if (current_frame == MAX_FRAMES - 1) {
			current_frame = 1;
		}
		enemies_process(current_frame);

		// drawing
		win_draw();
		enemies_draw();
		player_draw();
		log_draw();

		if (enemies_is_collided_with_player()) {
			_init();
		}

		// input
		ch = getch();
		player_process_input(ch);

		refresh();
		timeout(MILLIS_IN_FRAME);


	}
}
