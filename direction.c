#include <CCORE.h>
#include "window.h"
#include "direction.h"

void direction_move(Direction direction, uint *x, uint *y)
{
	uint limit = 0;
	const uint temp_x = *x;
	const uint temp_y = *y;
	switch (direction) {
		case Direction_Bottom: 
			limit = win_height - 1;
			*y = temp_y == limit ? limit : (temp_y + 1);
			break;
		case Direction_Left:
			limit = 1;
			*x = temp_x == limit ? limit : (temp_x - 1);
			break;
		case Direction_Top:
			limit = 1;
			*y = temp_y == limit ? limit : (temp_y - 1);
			break;
		case Direction_Right:
			limit = win_width - 1;
			*x = temp_x == limit ? limit : (temp_x + 1);
			break;
	}
}
