/********************************************************************
* 		copyright (C) 2014 all rights reserved
*			 @file: rs485.c
* 		  @Created: 2014-8-6 14:00
* 	  	   @Author: conway chen
* 	  @Description: test the rs485 function of sending and receiving 
*	  @Modify Date: 2014-8-6 14:00
*********************************************************************/
#include <stdio.h>
#include <termios.h>
#include <linux/ioctl.h>
#include <linux/serial.h>
#include <asm-generic/ioctls.h> /* TIOCGRS485 + TIOCSRS485 ioctl definitions */
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

/**
 * @brief: set the properties of serial port 
 * @Param: fd: file descriptor
 * @Param: nSpeed: Baud Rate
 * @Param: nBits: character size
 * @Param: nEvent: parity of serial port
 * @Param: nStop: stop bits
 */

typedef enum {DISABLE = 0, ENABLE} RS485_ENABLE_t;

int set_port(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;
	
	memset(&oldtio, 0, sizeof(oldtio));
	/* save the old serial port configuration */
	if(tcgetattr(fd, &oldtio) != 0) {
		perror("set_port/tcgetattr");
		return -1;	
	}
	
	memset(&newtio, 0, sizeof(newtio));
	/* ignore modem control lines and enable receiver */
	newtio.c_cflag = newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;	
	/* set character size */
	switch (nBits) {
		case 8: 
			newtio.c_cflag |= CS8;
			break;
		case 7: 
			newtio.c_cflag |= CS7;
			break;
		case 6: 
			newtio.c_cflag |= CS6;
			break;
		case 5: 
			newtio.c_cflag |= CS5;
			break;
		default:
			newtio.c_cflag |= CS8; 
			break;
	}
	/* set the parity */
	switch (nEvent) {
		case 'o':
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'e':
		case 'E':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case 'n':
		case 'N':
			newtio.c_cflag &= ~PARENB;
			break;
		default:
			newtio.c_cflag &= ~PARENB; 
			break;
	}
	/* set the stop bits */
	switch (nStop) {
		case 1:
			newtio.c_cflag &= ~CSTOPB;
			break;
		case 2:
			newtio.c_cflag |= CSTOPB;
			break;
		default:
			newtio.c_cflag &= ~CSTOPB; 
			break;	
	}	
	/* set output and input baud rate */
	switch (nSpeed) {
		case 0:
			cfsetospeed(&newtio, B0);
			cfsetispeed(&newtio, B0);
			break;
		case 50:
			cfsetospeed(&newtio, B50);
			cfsetispeed(&newtio, B50);
			break;
		case 75:
			cfsetospeed(&newtio, B75);
			cfsetispeed(&newtio, B75);
			break;
		case 110:
			cfsetospeed(&newtio, B110);
			cfsetispeed(&newtio, B110);
			break;
		case 134:
			cfsetospeed(&newtio, B134);
			cfsetispeed(&newtio, B134);
			break;
		case 150:
			cfsetospeed(&newtio, B150);
			cfsetispeed(&newtio, B150);
			break;
		case 200:
			cfsetospeed(&newtio, B200);
			cfsetispeed(&newtio, B200);
			break;
		case 300:
			cfsetospeed(&newtio, B300);
			cfsetispeed(&newtio, B300);
			break;
		case 600:
			cfsetospeed(&newtio, B600);
			cfsetispeed(&newtio, B600);
			break;
		case 1200:
			cfsetospeed(&newtio, B1200);
			cfsetispeed(&newtio, B1200);
			break;
		case 1800:
			cfsetospeed(&newtio, B1800);
			cfsetispeed(&newtio, B1800);
			break;
		case 2400:
			cfsetospeed(&newtio, B2400);
			cfsetispeed(&newtio, B2400);
			break;
		case 4800:
			cfsetospeed(&newtio, B4800);
			cfsetispeed(&newtio, B4800);
			break;
		case 9600:
			cfsetospeed(&newtio, B9600);
			cfsetispeed(&newtio, B9600);
			break;
		case 19200:
			cfsetospeed(&newtio, B19200);
			cfsetispeed(&newtio, B19200);
			break;
		case 38400:
			cfsetospeed(&newtio, B38400);
			cfsetispeed(&newtio, B38400);
			break;
		case 57600:
			cfsetospeed(&newtio, B57600);
			cfsetispeed(&newtio, B57600);
			break;
		case 115200:
			cfsetospeed(&newtio, B115200);
			cfsetispeed(&newtio, B115200);
			break;
		case 230400:
			cfsetospeed(&newtio, B230400);
			cfsetispeed(&newtio, B230400);
			break;
		default:
			cfsetospeed(&newtio, B115200);
			cfsetispeed(&newtio, B115200);
			break;	
	}
	/* set timeout in deciseconds for non-canonical read */
	newtio.c_cc[VTIME] = 0;
	/* set minimum number of characters for non-canonical read */
	newtio.c_cc[VMIN] = 0;
	/* flushes data received but not read */
	tcflush(fd, TCIFLUSH);
	/* set the parameters associated with the terminal from 
		the termios structure and the change occurs immediately */
	if((tcsetattr(fd, TCSANOW, &newtio))!=0)
	{
		perror("set_port/tcsetattr");
		return -1;
	}
	
	return 0;
}

/**
 * @brief: open serial port 
 * @Param: dir: serial device path
 */
int open_port(char *dir)
{
	int fd ;
	fd = open(dir, O_RDWR);
	if(fd < 0) {
		perror("open_port");	
	}	
	return fd;
}

/**
 * @brief: print usage message 
 * @Param: stream: output device 
 * @Param: exit_code: error code which want to exit 
 */
void print_usage (FILE *stream, int exit_code)
{
    fprintf(stream, "Usage: option [ dev... ] \n");
    fprintf(stream,
            "\t-h  --help     Display this usage information.\n"
            "\t-d  --device   The device ttyS[0-3] or ttySCMA[0-1]\n"
	    "\t-b  --baudrate Set the baud rate you can select\n" 
	    "\t               [230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300]\n"
            "\t-s  --string   Write the device data\n"
	    "\t-e  --1 or 0   Write 1 to enable the rs485_mode(only at atmel)\n");
    exit(exit_code);
}

/* PC6 for enable*/
void rs485_enable_ya157c(void)
{
     system("echo 71 > sys/class/gpio/export");
     system("echo out > /sys/class/gpio/gpio71/direction");
     system("echo 1 > /sys/class/gpio/gpio71/value");
 }



/**
 * @brief: main function  
 * @Param: argc: number of parameters
 * @Param: argv: parameters list
 */

int rs485_enable(const int fd, const RS485_ENABLE_t enable)
{
        struct serial_rs485 rs485conf;
        int res;

        /* Get configure from device */
        res = ioctl(fd, TIOCGRS485, &rs485conf);
        if (res < 0) {
                perror("Ioctl error on getting 485 configure:");
                close(fd);
                return res;
        }

        /* Set enable/disable to configure */
        if (enable) {   // Enable rs485 mode
                rs485conf.flags |= SER_RS485_ENABLED;
        } else {        // Disable rs485 mode
                rs485conf.flags &= ~(SER_RS485_ENABLED);
        }

        rs485conf.delay_rts_before_send = 0x00000004;
        /* Set configure to device */
        res = ioctl(fd, TIOCSRS485, &rs485conf);
        if (res < 0) {
                perror("Ioctl error on setting 485 configure:");
                close(fd);
        }

        return res;
}

int change_bit_rs485(int fd,int value)
{

	struct serial_rs485 rs485conf;
	int res;

	/* Get configure from device */
	res = ioctl(fd, TIOCGRS485, &rs485conf);
	if (res < 0) {
		perror("Ioctl error on getting 485 configure:");
		close(fd);
		return res;
	}

	/*rs485 send - recv*/
	if(value==1)
		rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
	else if(value==0)
		rs485conf.flags &= ~SER_RS485_RTS_AFTER_SEND;
	else ;

	/* Set configure to device */
	res = ioctl(fd, TIOCSRS485, &rs485conf);
	if (res < 0) {
		perror("Ioctl error on setting 485 configure:");
		close(fd);
	}
    return res;

}


int main(int argc, char *argv[])
{
	char *write_buf = "MYiR UART TEST";
	char read_buf[100];
	int fd, i, len, nread,r;
	pid_t pid;
	int next_option;
	struct termios oldtio;	
	int speed ;
	char *device;
	int spee_flag = 0, device_flag = 0;
	const char *const short_options = "hd:s:b:e:";
	unsigned int ffl_cnt=0;

	const struct option long_options[] = {
		{ "help",   0, NULL, 'h'},
		{ "device", 1, NULL, 'd'},
		{ "string", 1, NULL, 's'},
		{ "baudrate", 1, NULL, 'b'},
		{ NULL,     0, NULL, 0  }
	};
	
	if (argc < 2) {
		print_usage (stdout, 0);
		exit(0);	
	}

	while (1) {
		next_option = getopt_long (argc, argv, short_options, long_options, NULL);
		if (next_option < 0)
			break;
		switch (next_option) {
			case 'h':
				print_usage (stdout, 0);
				break;
			case 'd':
				device = optarg;
				device_flag = 1;
				break;
			case 'b':
				speed = atoi(optarg);
				spee_flag = 1;
				break;
			case 's':
				write_buf = optarg;
				break;
			case 'e':
				r = atoi(optarg);
				break;
			case '?':
				print_usage (stderr, 1);
				break;
			default:
				abort ();
		}
	}
	
	if ((!device_flag)||(!spee_flag)) {
		print_usage (stderr, 1);
		exit(0);	
	}
		
	/* open serial port */
	fd = open_port(device);
	if (fd < 0) {
		perror("open failed");
		return -1;
	}
	if(r)
	{	
        rs485_enable_ya157c();
		//rs485_enable(fd,ENABLE);	
	}
	/* set serial port */
	i = set_port(fd, speed, 8, 'N', 1);
	if (i < 0) {
		perror("set_port failed");
		return -1;	
	}

		
    // send  4 
	write(fd, write_buf, strlen(write_buf));	
	write(fd, write_buf, strlen(write_buf));
	write(fd, write_buf, strlen(write_buf));
	write(fd, write_buf, strlen(write_buf));
	usleep(40000); // 40ms

        change_bit_rs485(fd,0); // recv mode 
//		usleep(500000);
		while (1) {

			nread = read(fd ,read_buf ,sizeof(read_buf));
	        if (nread > 0) {
	            printf("RECV[%3d]: ", nread);
	            for(i = 0; i < nread; i++)
	                printf("0x%02x ", read_buf[i]);
	            printf("\n");

                // send
				write(fd, write_buf, strlen(write_buf));	
				usleep(40000); // 40ms
				change_bit_rs485(fd,0);   // recv mode 

	        }
			usleep(1000);
		}				

	/* restore the old configuration */		
	tcsetattr(fd, TCSANOW, &oldtio);
	close(fd);
	return 0;
}











