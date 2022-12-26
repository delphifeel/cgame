#ifndef _LOG_H_
#define _LOG_H_

#include <CCORE.h>

void _log_fill_buffer(const char src[], uint src_len);

#define log_info(...) 	do {												\
	char _log_info_buffer[128];											\
	const uint _log_info_buffer_len = CORE_StrPrintf(_log_info_buffer, sizeof(_log_info_buffer), __VA_ARGS__);	\
	_log_fill_buffer(_log_info_buffer, _log_info_buffer_len);							\
} while (0)

void log_draw(void);

#endif
