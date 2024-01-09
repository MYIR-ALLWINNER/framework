#ifndef _ADAS_INTERFACE_H_
#define _ADAS_INTERFACE_H_
//#################################################################################
#ifdef ADAS_ENABLE
#include <MDASLibTypes.h>


typedef struct
{
	  int major;
	  int minor;
	  int build;
	  sResultLDW ldw_result;
	  sResultFCW fcw_result;
}ADASOUT_IF;

#endif

#endif
