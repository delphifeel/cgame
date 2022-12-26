#ifndef _ENEMIES_H_
#define _ENEMIES_H_

#include "direction.h"

void enemies_init(void);
void enemies_draw(uint current_frame);
void enemies_get_closest_to_player_direction(Direction *direction);
bool enemies_is_collided_with_player(void);

#endif
