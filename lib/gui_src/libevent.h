#include <stdbool.h>
typedef long time_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;
static bool t_input_running = false;

//struct timeval { time_t tv_sec; int tv_usec; };
#if defined(__NEED_struct_timeval) && !defined(__DEFINED_struct_timeval)
struct timeval { time_t tv_sec; int tv_usec; };
#define __DEFINED_struct_timeval
#endif
struct input_event {
	struct timeval time;
	uint16_t type;
	uint16_t code;
	uint32_t value;
};

void *event_init();
