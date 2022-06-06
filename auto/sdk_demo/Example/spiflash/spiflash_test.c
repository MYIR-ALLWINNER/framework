#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define EEPROM_DEVICE "/sys/devices/44000000.ocp/44e0b000.i2c/i2c-0/0-0050/eeprom"
#define EEPROM_MTD_DEVICE "/dev/mtdblock8"
#define TEST_STR "spiflash write/read test!"

int main(int argc, char** argv)
{
	int fd;
	struct stat eeprom_stat;
	char read_buf[32] = { '\0' };

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("open spiflash unsuccess\n");
		return;
	}

	if (stat(argv[2], &eeprom_stat) < 0) {
		perror("failed to get spiflash status");
	} else {
		printf("\nspiflash size: %d KB\n\n", eeprom_stat.st_size/1024);
	}
	
	printf("write \'%s\' to spiflash\n", TEST_STR);
	if (write(fd, TEST_STR, strlen(TEST_STR)) < 0) {
		perror("write to spiflash failed\n");
		return;
	}

	lseek(fd, 0, SEEK_SET);
	if (read(fd, read_buf, strlen(TEST_STR)) < 0) {
		printf("read back failed\n");
		return;
	}

	printf("\nget the following string from spiflash:\n%s\n\n", read_buf);
	
	return 0;
}
