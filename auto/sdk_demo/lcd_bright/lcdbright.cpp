/*
 * @Description: Adjust the LCD backlight brightness.
 * @Version: 1.0
 * @Author: tangjianxiong
 * @Date: 2021-08-02 19:03:12
 * @LastEditors: tangjianxiong
 * @LastEditTime: 2021-08-03 10:55:48
 * @FilePath: \sdk_demo\lcd_bright\lcdbright.cpp
 * Copyright (C) 2021 ALLWINNER. All rights reserved.
 */
#include <sys/ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "sunxi_display2.h"

#define MODULE_VERSION "V2.0.20220506"

int main(int argc, char **argv)
{
	printf("lcdbright test version:%s\n", MODULE_VERSION);
	unsigned long arg[4] = {0};
	int dispfd;
	int ret;
	int cmd = atoi(argv[1]);
	/* open disp dev */
	if ((dispfd = open("/dev/disp", O_RDWR)) == -1)
	{
		printf("open display device fail!\n");
		return -1;
	}

	switch (cmd)
	{
	case 1:
		/* get the brightness */
		{
			int bl = 0;
			arg[0] = 0; //显示通道0
			bl = ioctl(dispfd, DISP_LCD_GET_BRIGHTNESS, (void *)arg);
			printf("The brightness is %d\n", bl);
		}
		break;

	case 2:
	/* get the brightness */
	{
		int bl = atoi(argv[2]);
		arg[0] = 0; //显示通道0
		arg[1] = bl;
		ioctl(dispfd, DISP_LCD_SET_BRIGHTNESS, (void *)arg);
		printf("Set brightness to %d\n", bl);
	}
	break;

	case 3:
	/* enable the brightness */
	{
		
		arg[0] = 0;
		ioctl(dispfd, DISP_LCD_BACKLIGHT_ENABLE, (void *)arg);
		if (ret != 0)
			printf("DISP_LCD_BACKLIGHT_ENABLE FAILED!\n");
	}
	break;

	case 4:
	/* disable the brightness */
	{
		arg[0] = 0;
		ret=ioctl(dispfd, DISP_LCD_BACKLIGHT_DISABLE, (void *)arg);
		if(ret!=0)
			printf("DISP_LCD_BACKLIGHT_DISABLE FAILED!\n");
	}
	break;

	default:
		printf("please input right params!\n");
		break;
	}

	return 0;
}