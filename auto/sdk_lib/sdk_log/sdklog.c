#include "stdio.h"
#include "sdklog.h"
#include "stdlib.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#define LOG_BUF_SIZE	1024
#define  HAVE_LOCALTIME_R

int sdk__android_log_print(int prio, const char *tag, const char *fmt, ...)  
{  
    va_list ap;  
    char buf[LOG_BUF_SIZE];      
  
    va_start(ap, fmt);  
    vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);  
    va_end(ap);  
  
    return sdk_log_print(prio,tag,buf);//__android_log_write(prio, tag, buf);  
} 
static int sdkloglevel=3;
int sdk_log_setlevel(int prio)
{
	if((prio > 6)||(prio <0))
	{
		prio = 6;
	}
	printf("set sdk log level %d \r\n",prio);
	sdkloglevel=prio;
	return 0;
}
int sdk_log_print(int prio, const char *tag,const char *fmt, ...)
{
    va_list ap;
    char buf[LOG_BUF_SIZE];
	if(prio>=sdkloglevel)
		return 0;
		
#if defined(HAVE_LOCALTIME_R)    
	struct tm tmBuf;
#endif    
	struct tm* ptm;

 //time_t timep;
 //	time(&timep);
	
    struct timeval tv;
    //struct timezone tz;
	
    gettimeofday (&tv, NULL);
	
#if defined(HAVE_LOCALTIME_R)    
	ptm = localtime_r(&(tv.tv_sec), &tmBuf);
#else    
	ptm = localtime(&(tv.tv_sec));
#endif
char timeBuf[32];
strftime(timeBuf, sizeof(timeBuf), "%m-%d %H:%M:%S", ptm);

int nm=snprintf(buf,LOG_BUF_SIZE,"%s.%03ld  %s", timeBuf, tv.tv_usec / 1000,tag);

    va_start(ap, fmt);
    vsnprintf(buf+nm, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);
	int slen=strlen(buf);
	buf[slen]='\r';
	buf[slen+1]='\n';
	buf[slen+2]=0;
    return printf(buf);
}

void print_stacktrace()
{
    int size = 16;
    void * array[16];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i)
    {
        ALOGD("%s\n", stacktrace[i]);
    }
    free(stacktrace);
}
