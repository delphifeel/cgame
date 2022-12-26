#include <ncurses.h>
#include "window.h"

void win_draw(void) {
	// draw top and bottom border
	for (uint i = 0; i < win_width; i++) {
		mvprintw(0, i, "_");
		mvprintw(win_height, i, "_");
	}
	// draw left and right border
	for (uint i = 1; i <= win_height; i++) {
		mvprintw(i, 0, "|");
		mvprintw(i, win_width, "|");
	}
}
