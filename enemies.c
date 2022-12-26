#include <ncurses.h>
#include <CCORE.h>

#include "enemies.h"
#include "player.h"
#include "log.h"
#include "window.h"

typedef struct {
	uint x;
	uint y;
} EnemiesPos;

static const char ENEMY_SPRITE = '#';
static const uint enemies_far = 5;
static const uint enemies_count = 10;

static bool is_init = false;
static EnemiesPos _pos[enemies_count];
static Direction _closest_direction = Direction_Top;
static int _closest_distance_x = 0;
static int _closest_distance_y = 0;

static Direction _calc_move_direction(int difference_x, int difference_y)
{
	if (difference_y == 0) {
		return difference_x < 0 ? Direction_Right : Direction_Left;
	}
	if (difference_x == 0) {
		return difference_y < 0 ? Direction_Bottom : Direction_Top;
	} 

	int random_number = rand();
	if (random_number % 2 == 0) {
		return difference_x < 0 ? Direction_Right : Direction_Left;
	} 

	return difference_y < 0 ? Direction_Bottom : Direction_Top;
}

void enemies_init(void)
{
	int random_number = 0;
	for (uint i = 0; i < enemies_count; i++) {
		random_number = rand();
		_pos[i].x = (random_number % (win_width - enemies_far)) + enemies_far;
		_pos[i].y = (random_number % (win_height - enemies_far)) + enemies_far;
	}

	is_init = true;
}

bool enemies_is_collided_with_player(void)
{
	CORE_Assert(is_init == true);
	return (_closest_distance_x == 0) && (_closest_distance_y == 0);
}

void enemies_get_closest_to_player_direction(Direction *direction)
{
	CORE_Assert(is_init == true);
	CORE_AssertPointer(direction);
	
	*direction = _closest_direction;
}

void enemies_draw(uint current_frame)
{
	CORE_Assert(is_init == true);

	uint player_x = 0;
	uint player_y = 0;
	player_get_pos(&player_x, &player_y);

	// move enemies 
	uint iter_x = 0;
	uint iter_y = 0;
	bool distance_init = false;
	int distance_lowest_x = 0;
	int distance_lowest_y = 0;
	int difference_x = 0;
	int difference_y = 0;

	for (uint i = 0; i < enemies_count; i++) {
		iter_x = _pos[i].x;
		iter_y = _pos[i].y;

		difference_x = iter_x - player_x;
		difference_y = iter_y - player_y;
		if (!distance_init) {
			distance_lowest_x = difference_x;
			distance_lowest_y = difference_y;
			distance_init = true;
		} else if ( (abs(difference_x) + abs(difference_y)) < (abs(distance_lowest_x) + abs(distance_lowest_y)) ) 
		{
			distance_lowest_x = difference_x;
			distance_lowest_y = difference_y;
		}

		// move every 4th frame
		if (current_frame % 3 == 0) {
			const Direction direction = _calc_move_direction(difference_x, difference_y);
			direction_move(direction, &iter_x, &iter_y);
			_pos[i].x = iter_x;
			_pos[i].y = iter_y;
		}
		mvprintw(iter_y, iter_x, "%c", ENEMY_SPRITE);
	}

	_closest_distance_x = distance_lowest_x;
	_closest_distance_y = distance_lowest_y;

	// calc closest enemy direction
	if ((abs(distance_lowest_y) < abs(distance_lowest_x))) {
		_closest_direction = distance_lowest_x < 0 ? Direction_Left : Direction_Right;
	} else {
		_closest_direction = distance_lowest_y < 0 ? Direction_Top : Direction_Bottom;
	}
}
