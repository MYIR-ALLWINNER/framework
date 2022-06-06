#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<sys/time.h>
#include<fcntl.h>
#include<errno.h>
#include<linux/input.h>

int main(int argc, char *argv[])
{
	int ledn;
	char* tmp;
	int keys_fd;
	struct input_event t;
	
	keys_fd = open(argv[1], O_RDONLY);
	if (keys_fd <= 0)
	{
        printf ("open %s device error!\n",argv[1]);
	    return 0;
	}

	printf("Hit any key on board ......\n");
    
    while(1)
	{
        if (read(keys_fd, &t, sizeof(t)) == sizeof(t))
	    {
            if (t.type == EV_KEY)
		    if (t.value == 0 || t.value == 1)
		    {
		        printf ("key %d %s\n", t.code,(t.value) ? "Pressed" : "Released");
		        if(t.code==KEY_ESC)
		            break;
		    }
	    }
    }
	
    close (keys_fd);
    return 0;

}

