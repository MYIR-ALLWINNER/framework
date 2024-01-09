#include "config.h"
#include "upgrade.h"

static void usage(void)
{
	printf("usage:\n");
	printf("upgrade  <firmware_file> <rootfs_partitions_name>\n");
	return ;
}

int main(int argc, char* argv[])
{
	char *part;
    int ret = 0;

	part = NULL;
    if(argc < 3){
		printf("too few argument!!\n");
		usage();
		return ret;
    }

	ret = get_env();
	if(ret < 0){
		printf("parse command line failed!\n");
		return ret;	
	}

	memset(bak_bootdev, 0, sizeof(bak_bootdev));
	part = argv[2];
	if (part && part[0])
		snprintf(bak_bootdev, sizeof(bak_bootdev),  "/dev/%s", part);
	else{
		snprintf(bak_bootdev, sizeof(bak_bootdev), "%s", ROOTS_BAK);
		printf("invalid boot partitions for backup, use default %s!\n", ROOTS_BAK);
	}

	printf("backup is partitions: %s\n", bak_bootdev);
	ret = update_start(argv[1]);
	if (!ret){
		replace_bootdev("env");
		replace_bootdev("env-redund");
	}
	
	return ret;
}