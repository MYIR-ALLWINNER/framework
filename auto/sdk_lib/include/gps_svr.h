/*create by landsem@liuxueneng 20161115
 */
#ifndef GPS_SERVICE_H
#define GPS_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include <hardware.h>
#include <gps.h>

#define NAME_MAX    32
#define USER_MAX    128

typedef struct nmea_info{
    GpsUtcTime  timestamp;
    const char  *nmea;
    int         length;
}nmea_t;

enum msgtype
{
    GPS_MSG_LOCATION            = 0xFF01,
    GPS_MSG_STATUS              = 0xFF02,
    GPS_MSG_SV_STATUS           = 0xFF03,
    GPS_MSG_NMEA                = 0xFF04,
    GPS_MSG_CAPABILITIES        = 0xFF05,
    GPS_MSG_ACQUIRE_WAKELOCK    = 0xFF06,
    GPS_MSG_RELEASE_WAKELOCK    = 0xFF07,
    GPS_MSG_REQUEST_UTC_TIME    = 0xFF08,

};

typedef void(*usr_cb)(uint32_t msg_type, void *msg_data, void *usr_data);


/*before any client want to get gps data need one to start the gps_sys
*@0 gps_sys_start();
*@$ gps_sys_stop();
*/
/***************api interface process***********/
/*@1    define  and init linux_gps_t dev (especial name and cbs)
 *@2    id = linux_gps_register( &dev);
 *@3    linux_gps_open(id);     then you can deal with the gps_data with your callbacks
 *@4    linux_gps_close(id)
 *@5    linux_gps_unregister(id);
 */
/***************api interface process***********/

typedef struct linux_gps_device{
    const char*                 usr_name;
    usr_cb                      _usr_cb;
    void*                       usr_data;
    struct linux_gps_device*    next;
}linux_gps_t;



//************APIs************/
/************************/
int gps_sys_start(void);
void gps_sys_stop(void);
/************************/

int linux_gps_register(linux_gps_t *dev);
int linux_gps_unregister(linux_gps_t *dev);
//************APIs************/

#ifdef __cplusplus
}
#endif


#endif /* GPS_SERVICE_H */

