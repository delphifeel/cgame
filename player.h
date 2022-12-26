#ifndef _PLAYER_H_
#define _PLAYER_H_

void player_init(void);
void player_get_pos(uint *x, uint *y);
void player_draw(void);
void player_process_input(int ch);

#endif
