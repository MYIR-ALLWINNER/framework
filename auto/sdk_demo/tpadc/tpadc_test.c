#include<stdio.h>
#include<errno.h>
#include<linux/input.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

#define MODULE_VERSION "V2.0.20220506"

static void show_hex(void *buf, int size)
{
	while(size--) {
		printf("0x%02x ", *((char *)buf++));
	}
	printf("\n");
}

int main(int agrc, char** argv)
{
	printf("tpadc test version:%s\n", MODULE_VERSION);
	int x, y, ret, fd;
	struct input_event ts;
	char event_path[32];

	printf("Please press the screen and check the data! \n");
	printf("Press Ctrl + c exit the test! \n");

	if(agrc > 1 && strlen(argv[1]) < 3) {
		sprintf(event_path, "/dev/input/event%s", argv[1]);
	} else {
		sprintf(event_path, "/dev/input/event0");
	}

	fd = open(event_path, O_RDONLY);
	if(fd == -1) {
		printf("open %s file error \n", event_path);
		return -1;
	} else {
		printf("open %s file success \n", event_path);
	}

	while(1) {
		printf("\nWaiting for data...\n");
		memset(&ts, 0, sizeof(ts));
		ret = read(fd, &ts, sizeof(ts));
		if (ret < 0) {
			printf("Error on read()\n");
			continue;
		}
		else if(ret != sizeof(ts)) {
			printf("read() failed: expect %d but got %d\n", (int)sizeof(ts), ret);
			continue;
		}

		printf("Got data:\n");
		show_hex(&ts, sizeof(ts));

		if (ts.type == EV_SYN) {
			printf("End of input_event packet\n");
			continue;
		} else if (ts.type == EV_ABS) {
			if (ts.code == ABS_X) {
				x = ts.value;
				printf("get position x=%d\n", x);
			}
			if (ts.code == ABS_Y) {
				y = ts.value;
				printf("get position y=%d\n", y);
			} else
				printf("Unknown data of type EV_ABS\n");

		} else
			printf("Unknown data\n");
	}

	printf("EXIT\n");
	close(fd);
	return 0;
}
