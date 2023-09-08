#include "upgrade.h"

const char *cmdline = "/proc/cmdline";
int get_env(void)
{
	int fd;
	int size;
	char part[64];
	char name[64];
	char dest[256];
	char buf[512];
	char *start, *end, *pos;
	
	fd = open("/proc/cmdline", O_RDONLY);
	if(fd >= 0){
		read(fd, buf, sizeof(buf));
		start = strstr(buf, "partitions=");
		if(start != NULL){
			memset(dest, '\0', sizeof(dest));
			start += strlen("partitions=");
			end = strchr(start, ' ');
			if(end){
				size = end - start;
				memcpy(dest, start, size);
				dest[size] = ':';
				dest[size + 1] = '\0';
				memset(buf, '\0', sizeof(buf));
				strncpy(buf, dest, sizeof(dest));
			}		
	    }
		size = strlen(buf);
		if(size <= 1){
			printf("Can not to strip patitions informations from cmdline \n");
			return -1;
		}

        pos = buf;
		size = strlen(buf);
		while(size > 0){
		    start = strchr(pos, '@');
		    memcpy(name, pos, start - pos);
			name[start - pos] = '\0';
			start += 1;
			end = strchr(start, ':');
			memcpy(part, start, end - start);
			part[end - start] = '\0';
			snprintf(dest, sizeof(dest), "/dev/%s", part);
			setenv(name, dest, 1);

			size -= (end + 1 - pos);
			pos = end + 1;
		}
	}
	return 0;
}