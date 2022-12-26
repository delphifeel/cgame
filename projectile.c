#include <CCORE.h>
#include <ncurses.h>

#include "projectile.h"
#include "window.h"

static const char _SPRITE = '=';
static bool _is_fired = false;
static uint _x = 0;
static uint _y = 0;
static Direction _direction = Direction_Right;


void projectile_reset(void)
{
	_is_fired = false;
}

bool projectile_is_fired(void)
{
	return _is_fired;
}

void projectile_get_pos(uint *x, uint *y)
{
	CORE_Assert(_is_fired);
	*x = _x;
	*y = _y;
}

void projectile_fire(uint start_x, uint start_y, Direction direction)
{
	if (!projectile_can_fire()) {
		// already fired and not hit
		return;
	}
	_is_fired = true;
	_x = start_x;
	_y = start_y;
	_direction = direction;
}

bool projectile_can_fire(void)
{
	return !_is_fired;
}

void projectile_draw(void)
{
	if (!_is_fired) {
		return;
	}

	mvprintw(_y, _x, "%c", _SPRITE);

	switch (_direction) {
		case Direction_Top:
			if (_y == 1) {
				_is_fired = false;
				return;
			}
			_y--; 
			break;
		case Direction_Right:
			if (_x == win_width - 1) {
				_is_fired = false;
				return;
			}
			_x++; 
			break;
		case Direction_Bottom: 
			if (_y == win_height - 1) {
				_is_fired = false;
				return;
			}
			_y++; 
			break;
		case Direction_Left:
			if (_x == 1) {
				_is_fired = false;
				return;
			}
			_x--; 
			break;
	}
}
