#include <CCORE.h>
#include <ncurses.h>

#include "window.h"
#include "player.h"
#include "projectile.h"
#include "log.h"
#include "enemies.h"

static const char PLAYER_SPRITE = '@';
static uint player_x = 1;
static uint player_y = 1;


void _fire(void)
{
	Direction enemy_direction = Direction_Top;
	enemies_get_closest_to_player_direction(&enemy_direction);

	uint projectile_x = player_x;
	uint projectile_y = player_y;
	Direction projectile_direction = enemy_direction;
	direction_move(projectile_direction, &projectile_x, &projectile_y);
	projectile_fire(projectile_x, projectile_y, projectile_direction);
}

void player_init(void)
{
	player_x = 1;
	player_y = 1;
}

void player_get_pos(uint *x, uint *y)
{
	CORE_AssertPointer(x);
	CORE_AssertPointer(y);

	*x = player_x;
	*y = player_y;
}

void player_draw(void)
{
	mvprintw(player_y, player_x, "%c", PLAYER_SPRITE);
	projectile_draw();
}

void player_process_input(int ch)
{
	Direction move_direction = Direction_Top;
	// move player
	switch (ch) {
		case KEY_UP:
			direction_move(Direction_Top, &player_x, &player_y);
			return;
		case KEY_DOWN:
			direction_move(Direction_Bottom, &player_x, &player_y);
			return;
		case KEY_LEFT:
			direction_move(Direction_Left, &player_x, &player_y);
			return;
		case KEY_RIGHT:
			direction_move(Direction_Right, &player_x, &player_y);
			return;
	}

	if ( (ch == ' ') && (projectile_can_fire()) ) {
		_fire();
	}
}
