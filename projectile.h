#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "direction.h"

void projectile_fire(uint start_x, uint start_y, Direction direction);
bool projectile_can_fire(void);
void projectile_draw(void);

#endif
