#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "aw_ini_parser.h"


/**
 * This enum stores the status for each parsed line (internal use only).
 */
typedef enum _line_status_ {
    LINE_UNPROCESSED,
    LINE_ERROR,
    LINE_EMPTY,
    LINE_COMMENT,
    LINE_SECTION,
    LINE_VALUE
} line_status ;



struct ini_struct {
	char *section;
	char *key;
	char *val;
};

/*-------------------------------------------------------------------------*/
/**
  @brief    Remove blanks at the beginning and the end of a string.
  @param    s   String to parse.
  @return   ptr to statically allocated string.

  This function returns a pointer to a statically allocated string,
  which is identical to the input string, except that all blank
  characters at the end and the beg. of the string have been removed.
  Do not free or modify the returned string! Since the returned string
  is statically allocated, it will be modified at each function call
  (not re-entrant).
 */
/*--------------------------------------------------------------------------*/
static char * strstrip(const char * s)
{
    static char l[ASCIILINESZ+1];
    char * last ;
    
    if (s==NULL) return NULL ;
    
    while (isspace((int)*s) && *s) s++;
    memset(l, 0, ASCIILINESZ+1);
    strcpy(l, s);
    last = l + strlen(l);
    while (last > l) {
        if (!isspace((int)*(last-1)))
            break ;
        last -- ;
    }
    *last = (char)0;
    return (char*)l ;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Initialize an ini file 
  @param    filename Name of the ini file to read.
  @return   int 0 if Ok, -1 otherwise.

  	open an ini file and alloc some buffer
 */
/*--------------------------------------------------------------------------*/
static int zalloc_buf(struct ini_struct *ini)
{
	ini->section = (char *)malloc(ASCIILINESZ+1);
	if(ini->section == NULL) {
        fprintf(stderr, "iniparser: cannot allocate memory\n");
		return -1;
	}
	
	ini->key = (char *)malloc(ASCIILINESZ+1);
	if(ini->key == NULL) {
        fprintf(stderr, "iniparser: cannot allocate memory\n");
		free(ini->section);
		return -1;
	}	
	
	ini->val = (char *)malloc(ASCIILINESZ+1);
	if(ini->val == NULL) {
        fprintf(stderr, "iniparser: cannot allocate memory\n");
		free(ini->section);
		free(ini->key);
		return -1;
	}
	
    memset(ini->section, 0, ASCIILINESZ+1);
    memset(ini->key,     0, ASCIILINESZ+1);
    memset(ini->val,     0, ASCIILINESZ+1);

    return 0;
}

static void free_buf(struct ini_struct *ini)
{
    free(ini->section);
    free(ini->key);
    free(ini->val);
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Load a single line from an INI file
  @param    input_line  Input line, may be concatenated multi-line input
  @param    section     Output space to store section
  @param    key         Output space to store key
  @param    value       Output space to store value
  @return   line_status value
 */
/*--------------------------------------------------------------------------*/
static line_status iniparser_line(
    char * input_line,
    char * section,
    char * key,
    char * value)
{   
    line_status sta ;
    int         len ;

    strcpy(input_line, strstrip(input_line));
    len = (int)strlen(input_line);

    sta = LINE_UNPROCESSED ;
    if (len<1) {
        /* Empty line */
        sta = LINE_EMPTY ;
    } else if (input_line[0]=='#' || input_line[0]==';') {
        /* Comment line */
        sta = LINE_COMMENT ; 
    } else if (input_line[0]=='[' && input_line[len-1]==']') {
        /* Section name */
        sscanf(input_line, "[%[^]]", section);
        strcpy(section, strstrip(section)); 
//        strcpy(section, strlwc(section));  /* Convert to lowercase. */
        sta = LINE_SECTION ;
    } else if (sscanf (input_line, "%[^=] = \"%[^\"]\"", key, value) == 2
           ||  sscanf (input_line, "%[^=] = '%[^\']'",   key, value) == 2
           ||  sscanf (input_line, "%[^=] = %[^;#]",     key, value) == 2) {
        /* Usual key=value, with or without comments */
        strcpy(key, strstrip(key));
//       strcpy(key, strlwc(key)); /* Convert to lowercase. */
        strcpy(value, strstrip(value));
        /*
         * sscanf cannot handle '' or "" as empty values
         * this is done here
         */
        if (!strcmp(value, "\"\"") || (!strcmp(value, "''"))) {
            value[0]=0 ;
        }
        sta = LINE_VALUE ;
    } else if (sscanf(input_line, "%[^=] = %[;#]", key, value)==2
           ||  sscanf(input_line, "%[^=] %[=]", key, value) == 2) {
        /*
         * Special cases:
         * key=
         * key=;
         * key=#
         */
        strcpy(key, strstrip(key));
//       strcpy(key, strlwc(key)); /* Convert to lowercase. */
        value[0]=0 ;
        sta = LINE_VALUE ;
    } else {
        /* Generate syntax error */
        sta = LINE_ERROR ;
    }
    return sta ;
}



/*-------------------------------------------------------------------------*/
/**
  @brief       Find the key position in the ini file
  @param    file 	Ini file name
  @param    key_value 	key and value(format  key:value).
  @param  start	the starting position will be returned here
  @return   int 		return the key size.

  The end positon is *start plus key size
 */
/*--------------------------------------------------------------------------*/
static int confirm_location_of_key(FILE *ini_filep, const char *section, const char *key, int *start)
{
	int len = 0;
	int ret = 0;
	int lineno = 0;
	struct ini_struct ini_st;
	char line[ASCIILINESZ+1];
	
	if(!section || !key || !start) {
		fprintf(stderr, "iniparser:confirm_lacation_of_key: invalid param");
		return -1;
	}
	
	if(zalloc_buf(&ini_st) != 0) {
		fprintf(stderr,
				"iniparser: allocate memory error\n");
		return -1;
	}

	memset(line, 0, ASCIILINESZ+1);

	while (fgets(line, ASCIILINESZ+1, ini_filep) != NULL) {
		lineno++ ;
		/* get current line lenghth */
		len = strlen(line) - 1;
		ret = len;
        /* Safety check against buffer overflows */
        if (line[len]!='\n') {
            fprintf(stderr,
                    "iniparser: input line too long(%d)\n", lineno);
			free_buf(&ini_st);
            return -1 ;
        }
        /* Get rid of \n and spaces at end of line */
        while ((len >= 0) &&
                ((line[len] == '\n') || (isspace(line[len])))) {
            line[len] = 0 ;
            len-- ;
        }
        /* Detect multi-line */
        if (line[len]=='\\') {
            /* Multi-line value */
            continue ;
        }

		if(iniparser_line(line, ini_st.section, ini_st.key, ini_st.val) == LINE_VALUE) {
		    if(!strncmp(ini_st.section, section, strlen(section)) 
				&& !strncmp(ini_st.key, key, strlen(ini_st.key))) {
				if((len = ftell(ini_filep)) > -1) {
//					printf("len:%d",  len);
					*start = len - ret -1;
					free_buf(&ini_st);
					return ret;
				}
			}
		}
	}

    fprintf(stderr,
        "iniparser:confirm_location_of_key: can not confirm the location\n");
	free_buf(&ini_st);
	return -1;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Get the value according to the `section` and the `key` from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Return value to it according to the `section` and the `key`
  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

static int get_a_ini_value(const char *section, const char *key, char *val)
{
    int  last=0 ;
    int  len ;
    int  lineno=0 ;
    int  errs=0;
    int  found = 0;
	struct ini_struct ini_st;
	char line[ASCIILINESZ+1];
	FILE * ini_filep = NULL;
	if(!section || !key || !val) {
		fprintf(stdout, "iniparser: invalid param");
		return -1;
	}
	
    if (!ini_filep && (ini_filep = fopen(INI_PATH, "r")) == NULL) {
        fprintf(stdout, "iniparser: cannot open %s\n", INI_PATH);
        return -1 ;
    }

	if(zalloc_buf(&ini_st) != 0) {
		fprintf(stdout,
				"iniparser: allocate memory error\n");
		fclose(ini_filep);
		return -1;
	}
	
	memset(line, 0, ASCIILINESZ+1);

    while (fgets(line + last, ASCIILINESZ-last, ini_filep)!=NULL) {
        lineno++ ;
        len = (int)strlen(line)-1;
        if (len==0)
            continue;
        /* Safety check against buffer overflows */
	    if (line[len]!='\n' && len >= ASCIILINESZ) {
            fprintf(stdout,
                    "iniparser: input line too long in ini file (%d)\n",
                    lineno);
			free_buf(&ini_st);
			fclose(ini_filep);
            return -1 ;
        }
        /* Get rid of \n and spaces at end of line */
        while ((len>=0) &&
                ((line[len]=='\n') || (isspace(line[len])))) {
            line[len]=0 ;
            len-- ;
        }
        /* Detect multi-line */
        if (line[len]=='\\') {
            /* Multi-line value */
            last=len ;
            continue ;
        } else {
            last=0 ;
        }
        switch (iniparser_line(line, ini_st.section, ini_st.key, ini_st.val)) {
            case LINE_EMPTY:
            case LINE_COMMENT:
            break ;

            case LINE_SECTION:
                if(!strncmp(section, ini_st.section, strlen(section))) {
                    found = 1;
                }
            break ;

            case LINE_VALUE:
                if(found && !strncmp(key, ini_st.key, strlen(key))) {
//                    printf("%s:%s:%s\n",section, key, g_val);
					strncpy(val, ini_st.val, strlen(ini_st.val) + 1);
					free_buf(&ini_st);
					fclose(ini_filep);
					return 0;
                }
            break ;

            case LINE_ERROR:
            fprintf(stdout, "iniparser: syntax error in the ini file (%d):\n",
                    lineno);
            fprintf(stdout, "-> %s\n", line);
            errs++ ;
            break;

            default:
            break ;
        }
        last=0;
        if (errs > 0) {
            fprintf(stdout, "iniparser: error occur\n");
            break ;
        }
    }
	
	free_buf(&ini_st);
	fclose(ini_filep);
	return -1;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Get the value according to the `section` and the `key` from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Return value to it according to the `section` and the `key`
  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

static int set_a_ini_value(const char *section, const char *key, const char *val)
{
	int ret = -1, rt = 0;
	int start = 0, end = 0, pos_r = 0, pos_w = 0, offset = 0, size = 0;
	int len = 0;
	int cnt = 0;
	int fd = 0;
	char *tmp = NULL;
	char *buf;
	struct stat st;
	FILE * ini_filep = NULL;

    if (!ini_filep && (ini_filep = fopen(INI_PATH, "r+")) == NULL) {
        fprintf(stderr, "iniparser: cannot open %s\n", INI_PATH);
        return -1 ;
    }

	ret = confirm_location_of_key(ini_filep, section, key, &start);/* Muil-lines å????*/
	if(ret == -1) {
    	fprintf(stderr,"confirm location of %s fail\n", key);
		fclose(ini_filep);
		return -1;
	}
	end = start + ret;
	offset = strlen(key) + strlen(val);
	if(offset+1 <= ret) len = ret;
	else len = offset+1;
	
	fd = fileno(ini_filep);
	if(fstat(fd, &st) == -1) {
		fprintf(stderr,"get file stat fail\n");
		fclose(ini_filep);
		return -1;
	}
//	printf("st->blksize:%d\n", (int)st.st_blksize);
	tmp = (char *)malloc(len+1);
	if(!tmp) {
		fprintf(stderr, "iniparser: allocate memory error!\n");
		fclose(ini_filep);
		return -1;
	}
	buf = (char *)malloc(st.st_blksize);
	if(!buf) {
		fprintf(stderr, "iniparser: allocate memory error!\n");
		free(tmp);
		fclose(ini_filep);
		return -1;
	}	
	memset(tmp, ' ', len+1);
//	printf("start:%d end:%d ret:%d\n", start, end, ret);

	snprintf(tmp, len+1, "%s=%s", key, val);
	tmp[offset+1] = ' ';

	if(len <= ret) {  /*  */
		lseek(fd, start, SEEK_SET);
		if(write(fd, tmp, len) <= 0) {
			fprintf(stderr, "iniparser: write ini file error\n");
			rt = -1;
			goto out;
		}
		rt = 0;
		goto out;
	}

	offset = len - ret;
	if(lseek(fd, 0, SEEK_END) <= st.st_blksize) { /* file size is smaller than block size */
		lseek(fd, end, SEEK_SET);
		if((cnt = read(fd, buf, st.st_blksize)) < 0) {
			fprintf(stderr, "iniparser: read ini file error\n");
			rt = -1;
			goto out;

		}
		
		lseek(fd, end + offset, SEEK_SET);
		if(write(fd, buf, cnt) < cnt) {
			fprintf(stderr, "iniparser: write ini file error\n");
			rt = -1;
			goto out;
		}
		lseek(fd, start, SEEK_SET);
		if(write(fd, tmp, len) <= 0) {
			fprintf(stderr, "iniparser: write ini file error\n");
			rt = -1;
			goto out;
		}		
		rt = 0;
		goto out;
	}
	
	pos_w = lseek(fd, -(st.st_blksize - offset), SEEK_END);
	pos_r = pos_w - offset;

	if(pos_r < end) { /* the r/w position is in the last block size of the file */
		pos_r = end;
		pos_w = pos_r + offset;
		lseek(fd, pos_r, SEEK_SET);
		if((cnt = read(fd, buf, st.st_blksize)) < 0) {
			fprintf(stderr, "iniparser: read ini file error\n");
			rt = -1;
			goto out;
		}
		
		lseek(fd, pos_w, SEEK_SET);
		if(write(fd, buf, cnt) < cnt) {
			fprintf(stderr, "iniparser: write ini file error\n");		
			rt = -1;
			goto out;
		}

		lseek(fd, start, SEEK_SET);
		if(write(fd, tmp, len) <= 0) {
			fprintf(stderr, "iniparser: write ini file error\n");
			rt = -1;
			goto out;

		}	
		rt = 0;
		goto out;

	} else { /* the general case */
		size = st.st_blksize;
		while(pos_r >= end) {
			lseek(fd, pos_r, SEEK_SET);
			if((cnt = read(fd, buf, size)) < 0) {
				fprintf(stderr, "iniparser: read ini file error\n");
				rt = -1;
				goto out;
			}
			lseek(fd, pos_w, SEEK_SET);
			if(write(fd, buf, cnt) < 0) {
				fprintf(stderr, "iniparser: write ini file error\n");
				rt = -1;
				goto out;
			}	
			if(pos_r == end) break;
			pos_r = pos_r -  st.st_blksize;
			pos_w = pos_w -  st.st_blksize;
			if(pos_r < end) {
				size = st.st_blksize - (end - pos_r);
				pos_r = end;
				pos_w = pos_r + offset;
			}
		}
	}

	lseek(fd, start, SEEK_SET);
	if(write(fd, tmp, len) <= 0) {
		fprintf(stderr, "iniparser: write ini file error\n");
		rt = -1;
		goto out;
	}	
	rt = 0;
	
out:
	free(tmp);
	free(buf);
	fsync(fd);
	fclose(ini_filep);
	return rt;
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the value type according to the `section` and the `key` from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted

  @return   int value type if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

static int get_ini_value_type(const char *section, const char *key)
{
	char *buf = NULL;
	int num = 0;
	char *endp = NULL;
	int type = 0;
	

	if(!section || !key) {
		fprintf(stderr, "iniparser: invalid param\n");
		return -1;		
	}

	buf = (char *)malloc(ASCIILINESZ + 1);
	if(!buf) {
		fprintf(stderr, "iniparser: allocate memory error\n");
		return -1;
	}
	memset(buf, 0, ASCIILINESZ + 1);

	if(get_a_ini_value(section, key, buf) == -1) {
		free(buf);
		return -1;
	}

	num = strtol(buf, &endp, 10);
	if(strlen(buf) && (endp - buf) == strlen(buf)) {
		type = VALUE_TYPE_NUM;
	} else if(strlen(buf)){
		type = VALUE_TYPE_STR;
	} else {
		type = VALUE_TYPE_UNKNOW;
	}


	free(buf);
	return type;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Get the value type according to the `section` and the `key` from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Return the value and the value type

  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

int get_ini_value(const char *section, const char *key, struct val_st *val)
{
	char *buf = NULL;
	int num = 0;
	char *endp = NULL;
	

	if(!section || !key || !val) {
		fprintf(stderr, "iniparser: invalid param\n");
		return -1;		
	}

	buf = (char *)malloc(ASCIILINESZ + 1);
	if(!buf) {
		fprintf(stderr, "iniparser: allocate memory error\n");
		return -1;
	}
	memset(buf, 0, ASCIILINESZ + 1);

	if(get_a_ini_value(section, key, buf) == -1) {
		free(buf);
		return -1;
	}

	num = strtol(buf, &endp, 10);

	if(strlen(buf) && (endp - buf) == strlen(buf)) {
		val->type = VALUE_TYPE_NUM;
		val->val.num = num;
	} else if(strlen(buf)){
		val->type = VALUE_TYPE_STR;
		snprintf(val->val.str, ASCIILINESZ + 1, "%s", buf);
	} else {
		val->type = VALUE_TYPE_UNKNOW;
		fprintf(stderr, "iniparser: find a unknown type\n");
	}

	free(buf);
	return 0;
}


/*-------------------------------------------------------------------------*/
/**
  @brief    Set the value according to the `section` , the `key` and the value type from ini file.
  @param    section  Section of the value u wanted
  		   key      Key of the Section u wanted
  		   val      Will be set to ini 

  @return   int 0 if Ok, -1 otherwise.
 */
/*--------------------------------------------------------------------------*/

int set_ini_value(const char *section, const char *key, struct val_st *val)
{
	char *buf = NULL;
	int ret = 0;
	int type = 0;

	if(!section || !key || !val) {
		fprintf(stderr, "iniparser: invalid param\n");
		return -1;		
	}

	if((type = get_ini_value_type(section, key)) != val->type || type == VALUE_TYPE_UNKNOW) {
		fprintf(stderr, "please check the value type\n");
//		return -1;		
	}

	buf = (char *)malloc(ASCIILINESZ + 1);
	if(!buf) {
		fprintf(stderr, "iniparser: allocate memory error\n");
		return -1;
	}
	memset(buf, 0, ASCIILINESZ + 1);
	
	switch(val->type) {
		case VALUE_TYPE_NUM:
			snprintf(buf, ASCIILINESZ + 1, "%d", val->val.num);
			break;
		case VALUE_TYPE_STR:
			snprintf(buf, ASCIILINESZ + 1, "%s", val->val.str);
			break;
		default:
			fprintf(stderr, "iniparser: unknown value type\n");
			free(buf);
			return -1;
	}

	ret = set_a_ini_value(section, key, (const char *)buf);
	free(buf);

	return ret;
}

