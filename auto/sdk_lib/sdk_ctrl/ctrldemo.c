#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/input.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <ls_ctrl.h>
#include <math.h>

#define ctrl_dbg(x,arg...) 

#define ctrl_err(x,arg...) printf("[AW][CTRL_DEMO]"x,##arg)
#define ctrl_info(x,arg...) printf("[AW][CTRL_DEMO]"x,##arg)


#ifdef DEMO_TEST 

int main(int argc, char **argv)
{
    int ret = 0;
    int i = 300;
    int num=atoi(argv[1]);  //转为整形
   
    lcd_blk_ctrl((unsigned long)num);
    sleep(20);
    lcd_blk_ctrl_1((unsigned long)num);

    return 0;
}

#endif
