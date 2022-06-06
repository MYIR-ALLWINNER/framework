#ifndef __DIPROCESS__H__
#define __DIPROCESS__H__

#include <sys/mman.h>
//#include <cutils/log.h>
#include <fcntl.h>
//#include <utils/Errors.h>

//namespace android {
//using android::int;

#ifndef NO_ERROR
#define NO_ERROR 0L
#endif


class DiProcess{

public:
    /* Constructs DiProcess instance. */
    DiProcess();

    /* Destructs DiProcess instance. */
    ~DiProcess();

public:

    int init();
    void diProcess1(unsigned char *presrc, int pre_width, int pre_height,
                unsigned char *src, int src_width, int src_height, 
                unsigned char *dst, int dst_width, int dst_height,int nField);
                
    int diProcess2(unsigned char *pre_src, unsigned char *now_src, unsigned char *next_src,
                int src_width, int src_height, int in_format,
                unsigned char *dst, int dst_width, int dst_height,
                int out_format, int nField);
    int release();

private:
    int mDiFd;
    int mDiReqId;

};


#endif