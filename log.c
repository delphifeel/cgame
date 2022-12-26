#include <ncurses.h>
#include "log.h"
#include "window.h"

static char _log_buffer[128];
static uint _log_buffer_len = 0;

void _log_fill_buffer(const char src[], uint src_len)
{
	_log_buffer_len = src_len;
	CORE_StrCpy(_log_buffer, sizeof(_log_buffer), src);
}


void log_draw(void)
{
	if (_log_buffer_len == 0) {
		return;
	}

	mvprintw(win_height + 1, 0, _log_buffer);
}

