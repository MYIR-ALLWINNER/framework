/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//#define LOG_TAG "UART"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <fcntl.h>
#include <getopt.h>
#include <time.h>
#include <errno.h>
//#include <cutils/log.h>
//#include <cutils/atomic.h>


//#include <hardware/hardware.h>
//#include "uart.h"

#define SERIAL_NUM0 "/dev/ttyS0"
#define SERIAL_NUM1 "/dev/ttyS1"
#define SERIAL_NUM2 "/dev/ttyS2"
#define SERIAL_NUM3 "/dev/ttyS3"
#define SERIAL_NUM4 "/dev/ttyGS0"
#define SERIAL_NUM5 "/dev/ttyO1"
#define SERIAL_NUM6 "/dev/ttyO2"
#define SERIAL_NUM7 "/dev/ttyO3"

/*
serial_num :1, 2, 3
baund : 115200, 38400, 9600
dataBits : 5, 6, 7 ,8
stopBits : 1, 2
*/
struct termios newtio, oldtio;
int uart_openSerialPort(int serial_num, long baud, int dataBits, int stopBits)
{
    int fd;

    switch(serial_num)
    {
        case 0:
            fd = open(SERIAL_NUM0, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial0 error\n");
                return fd;
            }
            break;
        case 1:
            fd = open(SERIAL_NUM1, O_RDWR | O_NOCTTY);
	    printf("open ttyS1");
            if(0 > fd) {
                printf("open serial1 error\n");
                return fd;
            }
            break;
        case 2:
            fd = open(SERIAL_NUM2, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial2 error\n");
                return fd;
            }
            break;
        case 3:
            fd = open(SERIAL_NUM3, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial3 error\n");
            return fd;
            }
            break;
        case 4:
            fd = open(SERIAL_NUM4, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial4 error\n");
            return fd;
            }
            break;
        case 5:
            fd = open(SERIAL_NUM5, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial5 error\n");
            return fd;
            }
            break;
        case 6:
            fd = open(SERIAL_NUM6, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial6 error\n");
            return fd;
            }
            break;
        case 7:
            fd = open(SERIAL_NUM7, O_RDWR | O_NOCTTY);
            if(0 > fd) {
                printf("open serial7 error\n");
            return fd;
            }
            break;
        default:
            printf("uart device description error\n");
            return -1;
    }

    tcgetattr(fd , &oldtio);
    //tcgetattr(fd , &newtio);
    switch(baud)
    {
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        case 57600:
            cfsetispeed(&newtio, B57600);
            cfsetospeed(&newtio, B57600);
            break;
        //case 56000:
        //    cfsetispeed(&newtio, B56000);
        //    cfsetospeed(&newtio, B56000);
        //    break;
        case 38400:
            cfsetispeed(&newtio, B38400);
            cfsetospeed(&newtio, B38400);
            break;
        case 19200:
            cfsetispeed(&newtio, B19200);
            cfsetospeed(&newtio, B19200);
            break;
        //case 14400:
        //    cfsetispeed(&newtio, B14400);
        //    cfsetospeed(&newtio, B14400);
        //    break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 1200:
            cfsetispeed(&newtio, B1200);
            cfsetospeed(&newtio, B1200);
            break;
        case 600:
            cfsetispeed(&newtio, B600);
            cfsetospeed(&newtio, B600);
            break;
        case 300:
            cfsetispeed(&newtio, B300);
            cfsetospeed(&newtio, B300);
            break;
        default:
            printf("uart set baud error\n");
            return -1;
    }

    newtio.c_cflag &= ~CSIZE;
    switch(dataBits)
    {
        case 5:
            newtio.c_cflag |= CS5;
            break;
        case 6:
            newtio.c_cflag |= CS6;
            break;
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
        default:
            printf("uart set dataBits error\n");
            return -1;
    }
    switch(stopBits)
    {
        case 1:
            newtio.c_cflag &= ~CSTOPB;
            break;
        case 2:
            newtio.c_cflag |= CSTOPB;
            break;
        default:
            printf("uart set stopBits error\n");
            return -1;
    }

    newtio.c_cflag &= ~PARENB;
    newtio.c_cflag |= (CLOCAL | CREAD);

//    newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

//    newtio.c_oflag &= ~OPOST;
//    newtio.c_oflag &= ~(ONLCR | OCRNL);    //添加的

//    newtio.c_iflag &= ~(ICRNL | INLCR);
//    newtio.c_iflag &= ~(IXON | IXOFF | IXANY);    //添加的

//    tcflush(fd, TCIOFLUSH);

//    newtio.c_cc[VTIME] = 0;
//    newtio.c_cc[VMIN] = 0;

    if(0 != tcsetattr(fd ,TCSANOW, &newtio))
    {
        printf("uart tcsetattr error\n");
        close(fd);
        return -1;
    }
    return fd;
}

int writeSerial( int fd, unsigned char *data, int len)
{
    int ret;
    fd_set wrfds;
    struct timeval tv;

    FD_ZERO(&wrfds);
    FD_SET(fd, &wrfds);

    tv.tv_sec = 0;
    tv.tv_usec = 500;

    ret = select(fd + 1, NULL, &wrfds, NULL, &tv);
    if(0 > ret) {
        printf("uart write select error\n");
        return -1;
    }
    else if (ret == 0) {
        printf("uart write select timeout\n");
        return 0;
    }
    else {
//        printf("uart write string=%s,val=%d\n", data, strlen(data));
        //usleep(800);
        ret = write(fd, data, len);
        if(0 > ret) {
            printf("uart write error\n");
            return -1;
        }
        else {
            printf("write ret:%d\n",ret);
        return ret;
        }
    }
    return 0;
}

int readSerial( int fd, unsigned char *buf, int len)
{
    int ret;

    ret = read(fd, buf, len);
    if(0 > ret) {
        printf("uart read error\n");
        return -1;
    }
    else
        return ret;
}

int selectSerial( int fd, int sec, int usec,int time)
{
    int ret;
    fd_set rdfds;
    struct timeval tv;

    FD_ZERO(&rdfds);
    FD_SET(fd, &rdfds);

    tv.tv_sec = sec;
    tv.tv_usec = usec;

    ret = select(fd + 1, &rdfds, NULL, NULL, &tv);
    if(0 > ret) {
        printf("uart read select error\n");
        return -1;
    }
    else if (ret == 0){
        printf("uart read select timeout,read time:%d\n", time);
        return 0;
    }
    else {
//        printf("uart read select\n");
        return 1;
    }
}

void closeSerialPort(int fd)
{
    tcsetattr(fd ,TCSANOW, &oldtio);
    close(fd);
}


    /* supporting APIs go here */

unsigned char calculate_crc8(unsigned char crc8,unsigned char dat)
{
    unsigned char i;
    unsigned char fb;
    for(i=0;i<8;i++)
    {
        fb=(crc8&0x01)^(dat&0x01);
        crc8=crc8>>1;
        if(fb==1)crc8=crc8^0x8c;
        dat=dat>>1;
    }
    return(crc8);
}

int main(int argc, char *argv[])
{
    int fd;
    int i = 0;
    int ret = 0;
    int len = 0;
    char read_buf[4096];
    //char *write_buf = "1234567890\n\0";
    //char write_buf[64] = {0xB5,0x62,0x06,0x08,0x06,0x00,0x10,0x27,0x01,0x00,0x01,0x00,0x4D,0xDD};   //0.1
    //char write_buf[64] = {0xB5,0x62,0x06,0x08,0x06,0x00,0xE8,0x03,0x01,0x00,0x01,0x00,0x01,0x39};   //1
    char write_buf[64] = {0x01,0x02,0x03,0x04,0x05,0x06,0x05,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E};   //10
    //char write_buf[64] = {0xB5,0x62,0x06,0x08,0x06,0x00,0x32,0x00,0x01,0x00,0x01,0x00,0x48,0xe6};   //1
    //char write_buf[64] = {0xB5,0x62,0x06,0x08,0x06,0x3E8,0x00,0x01,0x00,0x01,0x48,0xe6};   //1
    //char write_buf[32] = {0xa8,0x02,0x6c,0x84}; //enter

    //char write_buf[64] = {0xDD,0x4D,0x00,0x01,0x00,0x27,0x10,0x10,0x00,0x06,0x08,0x06,0x62,0xB5};   //0.1

    //char write_buf[4] = {0x5A};
    char CRC = 0;
    int length;
    int fdf = 0;
	int num;

	num = atoi(argv[1]);
	printf("open serial %d\n",num);
    fd = uart_openSerialPort(num, 9600, 8, 1);
    if( 0 > fd)
    {
        printf("[UART] open error\n");
        return -1;
    }
    bzero(read_buf, sizeof(read_buf));
    writeSerial(fd, write_buf,14);
	int time = 0;

    while(1) {
        if(selectSerial(fd,10, 0, time) == 1) {
            memset(read_buf,0,4096);
            ret = readSerial(fd, read_buf, 4095);
            if(ret > 0)
            {
                len = strlen(read_buf);
                printf("read_buf=%s,read len :%d\n",read_buf,len);
                printf("**************read time :%d\n",time);
                time++;
            }
            else
            {
                printf("read err :%d\n",ret);
            }
        }    
    }

    closeSerialPort(fd);

    return 0;
}
