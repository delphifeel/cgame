#include <ncurses.h>
#include <CCORE.h>

#include "enemies.h"
#include "player.h"
#include "log.h"
#include "window.h"
#include "projectile.h"

typedef struct {
	uint x;
	uint y;
	bool is_active;
} EnemiesPos;

static const char ENEMY_SPRITE = '#';
static const uint _at_least_this_far = 5;
static const uint _count = 30;

static bool is_init = false;
static EnemiesPos _pos[_count];
static uint _dead_count = 0;
static Direction _closest_direction = Direction_Top;
static int _closest_distance_x = 0;
static int _closest_distance_y = 0;

static bool _all_enemies_dead(void)
{
	return _dead_count == _count;
}

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
	_dead_count = 0;
	int random_number = 0;
	for (uint i = 0; i < _count; i++) {
		random_number = rand();
		_pos[i].x = (random_number % (win_width - _at_least_this_far)) + _at_least_this_far;
		_pos[i].y = (random_number % (win_height - _at_least_this_far)) + _at_least_this_far;
		_pos[i].is_active = true;
	}

	is_init = true;
}

bool enemies_is_collided_with_player(void)
{
	CORE_Assert(is_init == true);
	if (_all_enemies_dead()) {
		return false;
	}
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

	uint iter_x = 0;
	uint iter_y = 0;
	bool iter_dead = false;
	bool distance_init = false;
	int distance_lowest_x = 0;
	int distance_lowest_y = 0;
	int difference_x = 0;
	int difference_y = 0;

	const bool proj_fired = projectile_is_fired();
	uint projectile_x = 0;
	uint projectile_y = 0;
	if (proj_fired) {
		projectile_get_pos(&projectile_x, &projectile_y);
	}

	// for every enemy ...
	for (uint i = 0; i < _count; i++) {
		iter_x = _pos[i].x;
		iter_y = _pos[i].y;
		iter_dead = !_pos[i].is_active;

		if (iter_dead) {
			continue;
		}

		// is collision with projectile ?
		if ( (proj_fired) && 
		     (projectile_x == iter_x) &&
		     (projectile_y == iter_y) )
		{
			// enemy dead
			_pos[i].is_active = false;
			_dead_count++;

			projectile_reset();
			continue;
		}
		

		// calc closest enemy to player
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

		// move every 5th frame
		if (current_frame % 5 == 0) {
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
