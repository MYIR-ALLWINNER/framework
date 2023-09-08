#include "upgrade.h"

#define BLKREADBOOT0 _IO('v', 125)
#define BLKREADBOOT1 _IO('v', 126)
#define BLKBURNBOOT0 _IO('v', 127)
#define BLKBURNBOOT1 _IO('v', 128)

typedef struct {
    void* buffer;
    long len;
} burn_param_t;


static void usage(void)
{
	printf("Usage:\n");
	printf("uboot_update -boottype burn_file partname\n");
	printf("example:\n");
	printf("uboot_update -boot0 boot0.fex /dev/mtd0\n");
}

int burn_boot_main(int argc, char* argv[])
{
    int ret, fd, fd1;
    int boot_type = -1;
    struct stat st;
    char *buf, *bin, *part;
    burn_param_t cookie;

    ret = -1;
    if(argc < 4){
        printf("too few argument\n");
		usage();
        return ret;
    }

	if (!strncmp("-boot0", argv[1], strlen("-boot0")))
		boot_type = 0;
	else if (!strncmp("-boot1", argv[1], strlen("-boot1")) ||
	         !strncmp("-uboot", argv[1], strlen("-uboot")))
		boot_type = 1;
		
	if (-1 == boot_type){
		printf("boot type: %s invalid!\n", argv[1]);
		return ret;
	}
		
    bin = argv[2];
    part = argv[3];

    if ((!bin || !bin[1]) || (!part || !part[1])){
        printf("invalid bin or part name!\n");
        return ret;
    }

    fd = open(bin,O_RDONLY);
    if (fd < 0){
        perror("Error: ");
        return ret;
    }

    fstat(fd, &st);
    buf = malloc(st.st_size);
    if (!buf){
        perror("Error: ");
        return ret;
    }
    ret = read(fd,buf,st.st_size);
    printf("read size = %d\r\n",ret);

    cookie.buffer = buf;
    cookie.len = st.st_size;
    printf("cookie.len = %ld\r\n",cookie.len);
    fd1 = open(part, O_RDWR);
    if (fd1 > 0){
        if (boot_type == 0)
            ret = ioctl(fd1, BLKBURNBOOT0, (unsigned long)&cookie);
        else if(boot_type == 1)
            ret = ioctl(fd1, BLKBURNBOOT1, (unsigned long)&cookie);
    }

    if (ret)
        printf("burnNandBoot0 failed ! errno is %d : %s\n", errno, strerror(errno));
    else
        printf("burnNandBoot0 succeed!\n");

    free(cookie.buffer);

    close(fd1);
    close(fd);

    return ret;
}
