#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
   
static const char default_rtc[] = "/dev/rtc0";
static char *program_name;

/**
 * @brief: print help message 
 */
static void help(void)
{        
	fprintf(stderr,
"\tUsage: %s [OPTION]...\n"
"\t-h,--help      help\n"
"\t-s,--set       set date/time given with you.\n\tinput format:./rtc_test [hour] [minute] [second] [year] [month] [day]\n"
"\t-r,--show      read hardware clock and print result\n"
"\n", program_name);
} 
 
/**
 * @brief: read RTC date and time 
 * @Param: fd: the file descriptor of rtc device  
 */
void rtc_read_time(int fd)
{
	int retval;
	struct rtc_time rtc_tm;
	
	/*read the RTC time/date*/
	retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
	if (retval == -1) {
		perror("RTC_RD_TIME ioctl");
		exit(errno);
	}

	fprintf(stderr, "\n\tCurrent RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n\n",
		rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
		rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

	
}

/**
 * @brief: set rtc date and time  
 * @Param: fd: the file descriptor of rtc device 
 * @Param: hour: the hour to set
 * @Param: minute: the minute to set 
 * @Param: second: the hour to set
 * @Param: year: the year to set
 * @Param: month: the month to set
 * @Param: day: the day to set
 */
void rtc_set_time(int fd, int hour, int minute, int second, int year, int month, int day)
{
	int retval;
	struct rtc_time rtc_tm;
	
	rtc_tm.tm_mday = day;
	rtc_tm.tm_mon = month - 1;
	rtc_tm.tm_year = year - 1900;
	rtc_tm.tm_hour = hour;
	rtc_tm.tm_min = minute;
	rtc_tm.tm_wday = rtc_tm.tm_yday = rtc_tm.tm_isdst = 0;
	rtc_tm.tm_sec = second;
	/*set the RTC time/date*/
	retval = ioctl(fd, RTC_SET_TIME, &rtc_tm);
	if (retval == -1) {
		perror("RTC_SET_TIME ioctl");
		exit(errno);
	}	
	
	fprintf(stderr, "\n\t\tdate/time is updated to:  %d-%d-%d, %02d:%02d:%02d.\n\n",
		rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
		rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
}

/**
 * @brief: main function  
 * @Param: argc: number of parameters
 * @Param: argv: parameters list
 */ 
int main(int argc, char *argv[])
{
	int fd, retval, c;
	int set_flag = 0, read_flag = 0;
	struct rtc_time rtc_tm;
	const char *rtc = default_rtc;
	
	struct option long_option[] =
    {
    	{"help", 0, NULL, 'h'},        
        {"set", 1, NULL, 's'},
        {"show", 0, NULL, 'r'},
        {NULL, 0, NULL, 0},
    };
    
    program_name = argv[0];    	
	
    while (1) {
    	if ((c = getopt_long(argc, argv, "hs:r", long_option, NULL)) < 0)
    		break;
    	switch (c) {
		case 'h':
				help();
				break;		
		case 's':
				if (argc < 8) {
				fprintf(stderr, "\n\t\ttime format error!\n\n");
				exit(errno);	
				}	
				set_flag = 1;
				break;
		case 'r':
				read_flag = 1;
				break;
		case '?':
				help();
				break;
		default:
				abort ();
    	}
    }
    
    /* open rtc device */
    fd = open(rtc, O_RDWR);
	if (fd ==  -1) {
		perror(rtc);
		exit(errno);
	}
	
	if (argc == 1) {
		rtc_read_time(fd);	
	}
    
    if (set_flag) 
		rtc_set_time(fd, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
	if (read_flag)
		rtc_read_time(fd);
    
    close(fd);

	return 0;
}
