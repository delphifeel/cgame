#ifndef _DIRECTION_H_
#define _DIRECTION_H_

typedef enum {
	Direction_Top,
	Direction_Right,
	Direction_Bottom,
	Direction_Left,
} Direction;

void direction_move(Direction direction, uint *x, uint *y);

#endif
