#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>

unsigned char rgb[3]={0,0,255};

static char *fbtypes[6] = {
	"PACKED_PIXELS",
	"PLANES",
	"INTERLEAVED_PLANES",
	"TEXT",
	"VGA_PLANES",
	"FOURCC",
};

unsigned int rgb2lcd_565(struct fb_var_screeninfo *info, unsigned char red, unsigned char green, unsigned char blue)
{
	return ((red>>(8-info->red.length))<<info->red.offset) | \
		   ((green>>(8-info->green.length))<<info->green.offset) | \
		   ((blue>>(8-info->blue.length))<<info->blue.offset);
}

unsigned int rgb2lcd_888(struct fb_var_screeninfo *info, unsigned char red, unsigned char green, unsigned char blue)
{
	return blue<<info->blue.offset | green<<info->green.offset | red<<info->red.offset;
}

int main(int argc, char *argv[])
{
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize = 0;
	char *fbp = 0;
	int x = 0, y = 0;
	long int location = 0;
	int tmp=0;
	unsigned int (*rgb2lcd)(struct fb_var_screeninfo *,unsigned char, unsigned char, unsigned char); 
	int sdelay = 1;
	unsigned char *pline = NULL;

	if (argc == 2) {
		tmp = atoi(argv[1]);
		if (tmp > 0 && tmp < 60) {
			sdelay = tmp;
		}
	}

	/* open device*/
	fbfd = open("/dev/fb0", O_RDWR);
	if (!fbfd) {
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}

	printf("The framebuffer device was opened successfully.\n");
 
	/* Get fixed screen information */
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		exit(2);
	}

	/* Get variable screen information */
	
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information.\n");
		exit(3);
	}
	
	/* show these information*/
	printf("vinfo.xres=%d\n",vinfo.xres);
	printf("vinfo.yres=%d\n",vinfo.yres);
	printf("vinfo.bits_per_bits=%d\n",vinfo.bits_per_pixel);//24
	printf("vinfo.xoffset=%d\n",vinfo.xoffset);
	printf("vinfo.yoffset=%d\n",vinfo.yoffset);
	printf("red.offset=%d\n", vinfo.red.offset);
	printf("green.offset=%d\n", vinfo.green.offset);
	printf("blue.offset=%d\n", vinfo.blue.offset);
	printf("transp.offset=%d\n", vinfo.transp.offset);
	printf("finfo.line_length=%d\n",finfo.line_length);
	printf("finfo.type = %s\n", fbtypes[finfo.type]);

	if (vinfo.bits_per_pixel != 16 && vinfo.bits_per_pixel != 24
		&& vinfo.bits_per_pixel != 32) {
		printf("Unsupported bpp %d! Only support 16/24/32.\n", vinfo.bits_per_pixel);
		exit(4);
	}

	if (vinfo.bits_per_pixel == 16)
		rgb2lcd = rgb2lcd_565;
	else
		rgb2lcd = rgb2lcd_888;

	/* Figure out the size of the screen in bytes */
	screensize = finfo.line_length * vinfo.yres;
 
 	/* Map the device to memory */
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0); 
 	if ((int)fbp == -1) { 
		printf("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}

	printf("The framebuffer device was mapped to memory successfully.\n");
	memset(fbp,0,screensize);
	
	/* Where we are going to put the pixel */
	unsigned int color[8];
	color[0] = rgb2lcd(&vinfo, 0xFF, 0x00, 0x00);/* red */
	color[1] = rgb2lcd(&vinfo, 0x00, 0xFF, 0x00);/* green */
	color[2] = rgb2lcd(&vinfo, 0x00, 0x00, 0xFF);/* blue */
	color[3] = rgb2lcd(&vinfo, 0xFF, 0xFF, 0x00);/* r & g */
	color[4] = rgb2lcd(&vinfo, 0x00, 0xFF, 0xFF);/* g & b */
	color[5] = rgb2lcd(&vinfo, 0xFF, 0x00, 0xFF);/* r & b */
	color[6] = rgb2lcd(&vinfo, 0xFF, 0xFF, 0xFF);/* white */
	color[7] = rgb2lcd(&vinfo, 0x00, 0x00, 0x00);/* black */
	unsigned char *names[8] = {
		"red",
		"green",
		"blue", 
		"r & g", 
		"g & b",
		"r & b",
		"white",
		"black",
	};
	
	int i;
	for(i=0;i<8;i++){

		//color[i] = rgb2lcd(&vinfo, (i&0x04)?255:0, (i&0x02)?255:0, (i&0x01)?255:0);

		printf("color: %s   rgb_val: %08X\n", names[i], color[i]);

		for(x=0;x<vinfo.xres;x++){
			for(y=0;y<vinfo.yres;y++){
				location = (x+vinfo.xoffset)*(vinfo.bits_per_pixel/8) + (y+vinfo.yoffset)*finfo.line_length;
				*(fbp+location)= color[i]&0xFF;
				*(fbp+location+1)=(color[i]>>8)&0xFF;
				if (vinfo.bits_per_pixel > 16) {
					*(fbp+location+2)=(color[i]>>16)&0xFF;
				}
				if (vinfo.bits_per_pixel > 24) {
					*(fbp+location+3)=(color[i]>>24)&0xFF;
				}
			}
		}
		sleep(sdelay);
	}
	
	pline = (unsigned char *)malloc(finfo.line_length*3);
	memset(pline, 0, finfo.line_length*3);
	char r=255,g=0,b=0;
	unsigned int val = 0, j;
	for(i=0;i<vinfo.xres*3;i++) {
		location = i*vinfo.bits_per_pixel/8;
		val = rgb2lcd(&vinfo, r, g, b);
		for (j=0;j<vinfo.bits_per_pixel/8;j++) {
			pline[location+j] = (val>>(j*8))&0xFF;
		}
		//printf("(%d, %d, %d)\n", r, g, b);
		//printf("pline[%d]: %3X, i:%d, value: %8X\n", 
		//	location, pline[location],i, val); 
		if (r == 255 && g < 255 && b == 0) {
			g ++;
		} else if (g == 255 && r > 0) {
			r --;
		} else if (g == 255 && b < 255) {
			b ++;
		} else if (b == 255 && g > 0) {
			g --;
		} else if (b == 255 && r < 255) {
			r ++;
		} else if (r == 255 && b > 0) {
			b --;
		}
/*		if (r > 0 && g < 255 && b == 0) {
			r --;
			g ++;
		} else if (g > 0 && b < 255) {
			g --;
			b ++;
		} else if (b > 0 && r < 255) {
			b --;
			r ++;
		} */			
	}
	
	int pos[8] = {0}, height = (vinfo.yres-40)/3;
	for (i=1;i<8;i++) {
		if (i % 2 == 0)
			pos[i] = pos[i-1] + height;
		else
			pos[i] = pos[i-1] + 10;
	}
	j = vinfo.xres*vinfo.bits_per_pixel/8;
	for (i=0;i<vinfo.yres;i++)
	{
		location = (vinfo.xoffset)*(vinfo.bits_per_pixel/8) + (i+vinfo.yoffset)*finfo.line_length;
		if (i>=pos[1] && i<pos[2]) {
			memcpy(fbp+location, &pline[0], j);
		} else if (i>=pos[3] && i<pos[4]) {
			memcpy(fbp+location, &pline[j], j);
		} else if (i>=pos[5] && i<pos[6]) {
			memcpy(fbp+location, &pline[j*2], j);
		} else {
			//memset(fbp+location, 0, finfo.line_length);
			continue;
		}
	}
	
	free(pline);
	munmap(fbp, screensize); /* release the memory */
	
	while(1);
	close(fbfd);
	
	return 0;
}
