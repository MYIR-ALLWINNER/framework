#include <stdio.h>
#include <linux/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#define I2C_RETRIES 0x0701
#define I2C_TIMEOUT 0x0702
#define I2C_RDWR 0x0707 

// not include READ/WRITE bit
#define I2C_ADDR 0x50

struct i2c_msg
{
	unsigned short addr;
	unsigned short flags;
#define I2C_M_TEN 0x0010
#define I2C_M_RD 0x0001
	unsigned short len;
	unsigned char *buf;
};
struct i2c_rdwr_ioctl_data
{
	struct i2c_msg *msgs;
	int nmsgs; 
};

int main(int argc, char** argv){
	int fd,ret;
    char buf[100];
	struct i2c_rdwr_ioctl_data e2prom_data;

	//disable WP
	//system("echo 103 > /sys/class/gpio/export");
	//system("echo \"out\" > /sys/class/gpio/gpio103/direction");
	//system("echo 0 > /sys/class/gpio/gpio103/value");

	fd = open(argv[1],O_RDWR);

	if(fd<0){
		perror("open error");
	}

	e2prom_data.nmsgs=2; 

	e2prom_data.msgs=(struct i2c_msg*)malloc(e2prom_data.nmsgs*sizeof(struct i2c_msg));
	if(!e2prom_data.msgs)
	{
		perror("malloc error");
		exit(1);
	}
	ioctl(fd,I2C_TIMEOUT,1);
	ioctl(fd,I2C_RETRIES,2);
	/* write data to e2prom */
	e2prom_data.nmsgs=1;
	(e2prom_data.msgs[0]).len = 6;
	(e2prom_data.msgs[0]).addr = I2C_ADDR;
	(e2prom_data.msgs[0]).flags = 0; //write
	(e2prom_data.msgs[0]).buf = (unsigned char*)malloc(6);
	(e2prom_data.msgs[0]).buf[0] = 0x00;// e2prom addr[15:8] 
	(e2prom_data.msgs[0]).buf[1] = 0x00;//e2prom addr[7:0] 
	(e2prom_data.msgs[0]).buf[2] = 0x55;//the data to write byte0
	(e2prom_data.msgs[0]).buf[3] = 0x66;//the data to write byte1
	(e2prom_data.msgs[0]).buf[4] = 0x77;//the data to write byte2
	(e2prom_data.msgs[0]).buf[5] = 0x88;//the data to write byte2

    ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
	if(ret<0)
	{
		perror("ioctl error1");
	}
	sleep(1);
	
    /* read data from e2prom */
	e2prom_data.nmsgs=2;
	(e2prom_data.msgs[0]).len=2;
	(e2prom_data.msgs[0]).addr=I2C_ADDR;
	(e2prom_data.msgs[0]).flags=0;
	(e2prom_data.msgs[0]).buf=(unsigned char*)malloc(2);
	(e2prom_data.msgs[0]).buf[0]=0x00;// e2prom addr[15:8] 
	(e2prom_data.msgs[0]).buf[1]=0x00;//e2prom addr[7:0] 

	(e2prom_data.msgs[1]).len=6;
	(e2prom_data.msgs[1]).addr=I2C_ADDR;
	(e2prom_data.msgs[1]).flags=I2C_M_RD;
	(e2prom_data.msgs[1]).buf=(unsigned char*)malloc(6);
	(e2prom_data.msgs[1]).buf[0]=0;
	(e2prom_data.msgs[1]).buf[1]=0;
	(e2prom_data.msgs[1]).buf[2]=0;
	(e2prom_data.msgs[1]).buf[3]=0;
	(e2prom_data.msgs[1]).buf[4]=0;
	(e2prom_data.msgs[1]).buf[5]=0;

        ret=ioctl(fd,I2C_RDWR,(unsigned long)&e2prom_data);
	if(ret<0)
	{
		perror("ioctl error2");
	}
	printf("Read back:0x%02X\n\r",(e2prom_data.msgs[1]).buf[0]);
	printf("Read back:0x%02X\n\r",(e2prom_data.msgs[1]).buf[1]);
	printf("Read back:0x%02X\n\r",(e2prom_data.msgs[1]).buf[2]);
	printf("Read back:0x%02X\n\r",(e2prom_data.msgs[1]).buf[3]);

	close(fd);
	//system("echo 103 > /sys/class/gpio/unexport");

	return 0;
}
