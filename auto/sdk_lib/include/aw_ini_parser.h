
#ifndef AW_INI_PARSER
#define AW_INI_PARSER
#ifdef __cplusplus
extern "C" {
#endif

#define ASCIILINESZ     1023
#define INI_PATH        "/etc/dvrconfig.ini"

#define VALUE_TYPE_NUM 		1
#define VALUE_TYPE_STR		2
#define VALUE_TYPE_UNKNOW	0xff


struct val_st {
	int type; /* 1: number 2: string */
	union {
		int num;
		char str[ASCIILINESZ+1];
	}val;
};

//int iniparser_init(const char *filename);
//void iniparser_exit(void);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the value type according to the `section` and the `key` from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Return the value and the value type

  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

int get_ini_value(const char *section, const char *key, struct val_st *val);

/*-------------------------------------------------------------------------*/
/**
  @brief    Set the value according to the `section` , the `key` and the value type from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Will be set to ini 

  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

int set_ini_value(const char *section, const char *key, struct val_st *val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

