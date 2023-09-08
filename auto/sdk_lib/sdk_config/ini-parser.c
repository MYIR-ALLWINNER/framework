#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <cutils/log.h>
#include "aw_ini_parser.h"




int smain(int argc, const char **argv)
{

	if(argc > 3) {
		if(!strcmp(argv[2], "g")) {
			if(argc != 5) {
				ALOGE("You must input the following:\n");
				ALOGE("%s inifilename g setcion key\n", argv[0]);
				ALOGE("%s inifilename s setcion key value\n", argv[0]);	
				return -1;
			}
		}
		if(!strcmp(argv[2], "s")) {
			if(argc != 6) {
				ALOGE("You must input the following:\n");
				ALOGE("%s inifilename g setcion key\n", argv[0]);
				ALOGE("%s inifilename s setcion key value\n", argv[0]);	
				return -1;
			}
		}
	}else {
		ALOGE("You must input the following:\n");
		ALOGE("%s inifilename g setcion key\n", argv[0]);
		ALOGE("%s inifilename s setcion key value\n", argv[0]);	
		return -1;
	}
//	if(iniparser_init(argv[1]) == -1) {
//		printf("initialize iniparser error!\n");
//		return -1;
//	}
	if(!strcmp(argv[2], "g")) {
		struct val_st val;
		
		if(get_ini_value(argv[3], argv[4], &val) == -1) {
			ALOGE("get value err\n");
			return -1;
		}else {
			if(val.type == VALUE_TYPE_STR) printf("get a ini value str:%s\n", val.val.str);
			if(val.type == VALUE_TYPE_NUM) printf("get a ini value num:%d\n", val.val.num);
		}
		
	}else if(!strcmp(argv[2], "s")) {
		struct val_st val;
#if 0
		val.type = VALUE_TYPE_NUM;
		val.val.num = strtol(argv[5], NULL, 10);
		printf("val.val.num:%d\n", val.val.num);
#else
		val.type = VALUE_TYPE_STR;
		snprintf(val.val.str, ASCIILINESZ+1, "%s", argv[5]);
		ALOGD("val.val.str:%s\n", val.val.str);

#endif
		return set_ini_value(argv[3], argv[4], &val);
	} else {
		ALOGE("You must input the following:\n");
		ALOGE("%s inifilename g setcion key\n", argv[0]);
		ALOGE("%s inifilename s setcion key value\n", argv[0]);	
		return -1;
	}
//	iniparser_exit();

	return 0;
}
