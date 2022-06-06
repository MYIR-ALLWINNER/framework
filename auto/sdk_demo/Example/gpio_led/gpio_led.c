#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//#define DEBUG	1

#define ARRAY_SIZE(x)	(sizeof(x)/sizeof(x[0]))

#define LED_DELAY_US	(1000*1000) /* 200 ms */

#ifdef DEBUG
#define dbg_info(fmt, args...)		printf(fmt, #args)
#else
#define dbg_info(fmt, args...)
#endif

#define dbg_err(fmt, args...)		printf(fmt, #args)


typedef struct gpio_s {
	int gpio;
	char value_path[64];
	char dir_path[64];
	int value;
}gpio_t;
void leds_ctrl(const char **leds, int count, unsigned int status)
{
	int i = 0;
	char cmd[128] = {0};
	static unsigned int pre_status = 0;/* It was on by default */

	for (i = 0; i < count; i++, leds++) {
		if ((pre_status ^ status) & (1 << i)) {
			sprintf(cmd, "echo %d > %s", !!(status&(1 << i)), *leds);
			if (system(cmd)) {
				dbg_info("run cmd [%s] failed!\n", cmd);
			}
		}
	}
	pre_status = status;
}

int main (int argc, char *argv[])
{
	int keys_fd;
	char ret[2];
	struct input_event t[2];
	fd_set fds;
	struct timeval tv;
	const char* leds[]={argv[1]};
	keys_fd = open (argv[1], O_RDONLY);
	if (keys_fd <= 0) {
		dbg_err ("open %s device error!\n", argv[1]);
		return 0;
	}

    /* Set all LEDs to ON to info user for key pressing */
    while(1){
	    leds_ctrl(leds, ARRAY_SIZE(leds), 0xF);
	    usleep(LED_DELAY_US);
        leds_ctrl(leds, ARRAY_SIZE(leds), 0);
	    usleep(LED_DELAY_US);
    }
	
	
	return 0;
}

