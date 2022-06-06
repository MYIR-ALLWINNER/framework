#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/reboot.h>
#include <cutils/android_reboot.h>
#include <string.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <ls_ctrl.h>
#include <asoundlib.h>


#if 1
enum lcd_ctrl{
    //----lcd----
    DISP_LCD_ENABLE = 0x100,
    DISP_LCD_DISABLE = 0x101,
    DISP_LCD_SET_BRIGHTNESS = 0x102,
    DISP_LCD_GET_BRIGHTNESS = 0x103,
    DISP_LCD_BACKLIGHT_ENABLE  = 0x104,
    DISP_LCD_BACKLIGHT_DISABLE  = 0x105,
    DISP_LCD_SET_SRC = 0x106,
    DISP_LCD_SET_FPS  = 0x107,
    DISP_LCD_GET_FPS  = 0x108,
    DISP_LCD_GET_SIZE = 0x109,
    DISP_LCD_GET_MODEL_NAME = 0x10a,
    DISP_LCD_SET_GAMMA_TABLE = 0x10b,
    DISP_LCD_GAMMA_CORRECTION_ENABLE = 0x10c,
    DISP_LCD_GAMMA_CORRECTION_DISABLE = 0x10d,
    DISP_LCD_USER_DEFINED_FUNC = 0x10e,
    DISP_LCD_CHECK_OPEN_FINISH = 0x10f,
    DISP_LCD_CHECK_CLOSE_FINISH = 0x110,
};
#endif

#define     TINYMIX     1

#define     AUDIO_ON        "1"
#define     AUDIO_OFF       "0"

#define     LCD_ON          "1"
#define     LCD_OFF         "0"

#define AUDIO_DEVICE        "/sys/devices/platform/landsem_common.0/common_attr/ls_arm_mute"
#define LCD_BLK_DEVICE		"/dev/disp"
#define LCD_POWER_DEVICE    "/sys/devices/platform/landsem_blk.0/attrs/power"
#define RETRY_COUNT         5

#define DEV_DBG_EN   		0xFF

#define ctrl_dbg(x,arg...) 

#define ctrl_err(x,arg...) printf("[AW][LS_CTRL]"x,##arg)
#define ctrl_info(x,arg...) printf("[AW][LS_CTRL]"x,##arg)

#define Digital_volume      "1"
#define HeadPhone_volume    "2"
#define Max_volume          "63"

#define BUFFER_SIZE         1024

const char *volume_level[] = {
"0",
"24",
"28",
"32",
"36",
"40",
"43",
"45",
"47",
"49",
"51",
"54",
"55",
"56",
"57",
"58",
"59",
"60",
"61",
"62",
"63",
"63",
"63",
};

static int audio_fd = 0;
static int audio_init = 0;

static struct mixer *ls_mixer = NULL;
static int lcd_blk_fd = 0;
static int lcd_blk_init = 0;

static int lcd_power_fd = 0;
static int lcd_power_init = 0;

extern void tinymix_set_value(struct mixer *mixer, const char *control, char **values, unsigned int num_values);
extern struct mixer* mixer_open(unsigned int card);

//update //
char fw_name[4][128] = {};
//update //


int audio_ctrl_init(void)
{
    unsigned int card = 0;

    audio_fd = open(AUDIO_DEVICE, O_RDWR);
    if(audio_fd == -1) {
        ctrl_err("open %s file error!\n", AUDIO_DEVICE);
        return -1;
    }
    audio_init = 1;


    ls_mixer = mixer_open(card);
    if(NULL == ls_mixer)
    {
        fprintf(stderr, "Failed to open mixer\n");
        return -1;
    }
    system("tinymix 1 63");
    system("tinymix 2 58");
    ctrl_dbg("%s ok\n", __func__);
    return 0;
}


static int audio_ctrl(int val)
{
    int i = 0;
    int ret = 0;

    if((audio_init != 1) || audio_fd < 0)
    {
        ctrl_err("%s status wrong\n", __func__);
        return -1;
    }
    if( val == 0)
    {
        i = 0;
        while ( ret < strlen(AUDIO_OFF) && i++ < RETRY_COUNT)
        {
            ret = write(audio_fd, AUDIO_OFF, strlen(AUDIO_OFF));
            if( ret < 0)
                perror("write 0 error:\n");
            ctrl_dbg("%d %s AUDIO_OFF %d\n", i, __func__, ret);
        }
    }
    else 
    {
        i = 0;
        while ( ret < strlen(AUDIO_ON)  && i++ < RETRY_COUNT)
        {
            ret = write(audio_fd, AUDIO_ON, strlen(AUDIO_ON));
            if( ret < 0)
                perror("write 1 error:\n");
            ctrl_dbg("%d %s AUDIO_ON %d\n", i, __func__, ret);
        }
    }

    return 0;
}

int audio_on(void)
{
    return audio_ctrl(1);
}

int audio_off(void)
{
    return audio_ctrl(0);
}


int audio_volume_set(int level)
{
    static i = 0;

    if(level > 20)
        level = 20;
    else if(level < 0)
        level = 0;
    //tinymix_set_value(ls_mixer, "2", &volume_level[level], 1);
    tinymix_set_value(ls_mixer, HeadPhone_volume, &volume_level[level], 1);
    //ctrl_dbg("%s:set audio_volume_level: %d ok!\n", __func__, level);
    return 0;
}


int lcd_blk_ctrl_init(void)
{

    lcd_blk_fd = open(LCD_BLK_DEVICE, O_RDWR);
    if(lcd_blk_fd == -1) {
        ctrl_err("open %s file error!\n", LCD_BLK_DEVICE);
        return -1;
    }
    lcd_blk_init = 1;
    ctrl_dbg("%s ok\n", __func__);
    return 0;
}


int lcd_power_ctrl_init(void)
{

    lcd_power_fd = open(LCD_POWER_DEVICE, O_RDWR);
    if(lcd_power_fd == -1) {
        ctrl_err("open %s file error!\n", LCD_POWER_DEVICE);
        return -1;
    }
    lcd_power_init = 1;
    ctrl_dbg("%s ok\n", __func__);
    return 0;
}

static int lcd_power_ctrl(int val)
{
    int i = 0;
    int ret = 0;

    if((lcd_power_init != 1) || lcd_power_fd < 0)
    {
        ctrl_err("%s status wrong\n", __func__);
        return -1;
    }
    if( val == 0)
    {
        i = 0;
        while ( ret < strlen(LCD_OFF) && i++ < RETRY_COUNT)
        {
            ret = write(lcd_power_fd, LCD_OFF, strlen(LCD_OFF));
            if( ret < 0)
                perror("write 0 error:\n");
            ctrl_dbg("%d %s LCD_OFF %d\n", i, __func__, ret);
        }
    }
    else 
    {
        i = 0;
        while ( ret < strlen(LCD_ON)  && i++ < RETRY_COUNT)
        {
            ret = write(lcd_power_fd, LCD_ON, strlen(LCD_ON));
            if( ret < 0)
                perror("write 1 error:\n");
            ctrl_dbg("%d %s LCD_ON %d\n", i, __func__, ret);
        }
    }

    return 0;
}

int lcd_on(void)
{
    return lcd_power_ctrl(1);
}

int lcd_off(void)
{
    return lcd_power_ctrl(0);
}




int lcd_blk_ctrl(unsigned long val)
{
    unsigned long args[4] = {};
    int ret = 0;
    unsigned long brightness = 1;

    if((lcd_blk_init != 1) || lcd_blk_fd < 0)
    {
        ctrl_err("%s status wrong\n", __func__);
        return -1;
    }
    if (val <= 0)
        val = 0;
    else if(val > 20)
        val = 20;
    brightness =  1 + val * 13;

    args[0] = 0;
    args[1] = brightness;
    args[2] = 0;

    ret = ioctl(lcd_blk_fd, DISP_LCD_SET_BRIGHTNESS, (unsigned long)args);
    //ctrl_dbg("LCD_BRIGNTNESS_SET: %lu Ok\n", brightness);

    return 0;
}

void audio_ctrl_exit(void)
{
    if(audio_init){
	    audio_init = 0;
		if(audio_fd>0){
		    close(audio_fd); 
			audio_fd = 0;
			
			if(NULL != ls_mixer)
		    	mixer_close(ls_mixer);
		}
    }
    ctrl_dbg("%s ok\n", __func__);
}

void lcd_power_ctrl_exit(void)
{
   if(lcd_power_init){
    lcd_power_init = 0;
	if(lcd_power_fd >0)
	    close(lcd_power_fd); 
		lcd_power_fd = 0;
   	}
    ctrl_dbg("%s ok\n", __func__);
}

void lcd_blk_ctrl_exit(void)
{
   if(lcd_blk_init){
    lcd_blk_init = 0;
		if(lcd_blk_fd>0){
		    close(lcd_blk_fd); 
			lcd_blk_fd = 0;
		}
   	}
    ctrl_dbg("%s ok\n", __func__);
}


static int remove_file(const char *dir, int idx, const char *type)
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat statbuf = {};
    char key[4] = {};
   // char suffix[32] = {};

    if(NULL == dir || idx < 0 || NULL == type)
        return -1;
    sprintf(key, "%d-",idx);

    dp = opendir(dir);
    if( NULL == dp)
    {
        fprintf(stderr, "cannot open directory:%s\n", dir);
        return -2;
    }
    while(NULL != (entry = readdir(dp)))
    {
        lstat(entry->d_name, &statbuf);

        if( strstr(entry->d_name, key) && strstr(entry->d_name, type))
        {
            char buff[256] = {};

            memset(buff, 0 , sizeof(buff));
            sprintf(buff, "%s%s", dir, entry->d_name);
            if(0 == remove(buff))
                printf("remove_file:%s\n",buff);

            closedir(dp);
            return 0;

        }


    }
    closedir(dp);
    return 0;

}

static int get_file(const char *dir, const char *new_dir, int idx,  const char *type, char *old_name, char *new_name, int new_idx)
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat statbuf = {};
    char key[8] = {};

    if(NULL == dir || NULL == new_dir || idx < 0 || NULL == type|| NULL == old_name || NULL == new_name || old_name == new_name)
        return -1;
    sprintf(key, "%d-",idx);

    dp = opendir(dir);
    if( NULL == dp)
    {
        fprintf(stderr, "cannot open directory:%s\n", dir);
        return -2;
    }
    //travel the file
    while(NULL != (entry = readdir(dp)))
    {
        lstat(entry->d_name, &statbuf);

        if(strstr(entry->d_name, key) && strstr(entry->d_name, type))
        {
        // get the file
            sprintf(old_name, "%s%s", dir, entry->d_name);
            sprintf(new_name, "%s%s", new_dir, entry->d_name);
            char *p = strstr(new_name, type);
            char *p0 = strstr(new_name, key);
            char name[32] = {};
            if(p && p0)
            {
                sprintf(p,"%s%s","_lock", type);
                
                strcpy(name, p0+strlen(key));
                sprintf(p0,"%d-%s",new_idx,name);
                closedir(dp);
                return 0;
            }
            else
            {
                printf("file:%s add suffix lock failed\n", new_name);
                closedir(dp);
                return -1;
            }



        }


    }
    printf("dir:%s no match :%s*%s:file\n",dir, key, type);
    closedir(dp);
    return -3;

}


int lock_file_rename(int camera_id, int idx, const char *type, int new_idx)
{

    char old_name[64]  = {};
    char new_name[64]  = {};
    char *normal_video_dir[]  =  {"/mnt/UDISK/frontVideo/","/mnt/UDISK/rearVideo/"};
    char *picture_dir[]  =  {"/mnt/UDISK/frontPicture/","/mnt/UDISK/rearPicture/"};
    char *lock_video_dir  =  "/mnt/UDISK/lockVideo/";
    char *normal_thumb_dir[]  =  {"/mnt/UDISK/frontVideo/.thumb/","/mnt/UDISK/rearVideo/.thumb/"};
    char *lock_thumb_dir =  "/mnt/UDISK/lockVideo/.thumb/";
    char *rm_suffix[] = {"_front_lock","_rear_lock"};
    char *odir = NULL;
    char *ndir = NULL;
    int ret = 0;
    char *temp = NULL;
    char buff[256] = {};

    if(NULL == type || camera_id < 0 || camera_id > 1 || idx < 0 || type < 0  || new_idx < 0)
        return -1;

// get the file
    if(strstr(type, "mp4"))
    {
        odir = normal_video_dir[camera_id];
        ndir = lock_video_dir;
        if(access(lock_thumb_dir, R_OK | W_OK) &&  mkdir(lock_thumb_dir, 0666))
            printf("mkdir %s failed!\n", lock_thumb_dir);
    }
    else
    { 
        odir = picture_dir[camera_id];
        ndir = picture_dir[camera_id];
    }
    
    if(get_file(odir, ndir, idx, type, old_name, new_name, new_idx))
    {
        printf("get file  %d-*%s failed!\n", idx, type);
        return -2;  
    }
    // remove old file
    remove_file(ndir, new_idx, rm_suffix[camera_id]);

// rename the file
    if(rename(old_name, new_name))
    {
        fprintf(stderr, "rename  file failed %s->%s!\n", old_name, new_name);
        return -3;
    }
    printf("camera:%d rename idx %d(%s) -> new_idx %d(%s) OK!\n", camera_id,idx, old_name, new_idx,new_name);

    if(!strstr(type, "mp4"))
        return 0;
//get thumb file
    odir = normal_thumb_dir[camera_id];
    ndir = lock_thumb_dir;

    if(get_file(odir, ndir, idx, ".jpg", old_name, new_name, new_idx))
    {
        printf("get file  %d-*%sfailed!\n", idx, type);
        return -2;  
    }

    // remove old file
    remove_file(ndir, new_idx, type);
    // open the dir 
// rename the file
    if(rename(old_name, new_name))
    {
        fprintf(stderr, "rename  file failed %s->%s!\n", old_name, new_name);
        return -3;
    }
    printf("camera:%d rename idx %d(%s) -> new_idx %d(%s) OK!\n", camera_id,idx, old_name, new_idx,new_name);

    return 0;
}


int check_update(const char *version)
{
    char *dir = "/mnt/UDISK/";
    char *key[] = {"DvrUI", "libsdk.so", "autorun.sh","config.ini"};
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat statbuf = {};
    int fw = 0;
    char update_key[64] = {};
    char *op = version;
    char *pv = NULL;
    char *end = NULL;
    char new_version[64] = {};
   
    memset(new_version, 0, sizeof(new_version));
   // char suffix[32] = {};

    //if(NULL == key || NULL == name || num < 1)
    if(NULL == fw_name || NULL == version || strlen(version) < 20)
        return -1;

    if(access("/dev/mmcblk1p1", R_OK | W_OK))
        return -2;

    sprintf(update_key, "%s%.12s","update_v.", version);
    printf("update_key=%s\n",update_key);
    //sprintf(suffix, "%s%s", "_lock", type);
    dp = opendir(dir);
    if( NULL == dp)
    {
        fprintf(stderr, "cannot open directory:%s\n", dir);
        return -3;
    }
    printf("opendir ok\n");
    while(NULL != (entry = readdir(dp)))
    {
        lstat(entry->d_name, &statbuf);
        //if( strstr(entry->d_name, key[i]) )
        pv = strstr(entry->d_name, update_key);
        end = strstr(entry->d_name, ".tar");
        if( pv && end)
        {
            int i = 0;
            int l_op = strlen(op);
            int l_pv = strlen(pv);

            pv += strlen("update_v.");
            printf("po= %s op = %s\n", pv, op);
            //compare the old_version and new_version 
            while(l_op-- && l_pv-- && pv + i < end && pv[i] == op[i])
            {
                ++i;
            }

            // we a new version
            if(pv + i < end && pv[i] > op[i])
            {
                    memset(fw_name, 0, sizeof(fw_name));
                    sprintf(fw_name, "%s%s", dir, entry->d_name);
                    printf("%s get file:%s\n", __func__,fw_name);
                    fw = 1;
                break;
            }

        }
    }
    closedir(dp);
    printf("%s match update fw=%d\n", __func__, fw);
    return fw;

}

int ls_cp_file(const char *src_file, const char *dst_file)
{
    char buf[BUFFER_SIZE] = {};
    long f_size = 0;
    char *ptr = NULL;
    int r_num = 0;
    int w_num = 0;
    FILE *src = NULL;
    FILE *dst = NULL;

    if(src_file == NULL || dst_file == NULL || access(src_file, R_OK))
        return -1;


    src = fopen(src_file, "rb");
    if(NULL == src)  
    {
        fprintf(stderr,"fopen %s Error\n",src_file);
        goto Exit1;
    }

    dst = fopen(dst_file, "w+"); 
    if(NULL == dst) 
    {
        fprintf(stderr,"fopen %s Error\n",dst_file);
        goto Exit2;
    }

    memset(buf, 0, sizeof(buf));
    while((r_num = fread(buf, 1, BUFFER_SIZE, src)) > 0)
    {
            ptr = buf;
            while((w_num = fwrite(ptr, 1, r_num, dst)) > 0)
            {
                if(w_num == r_num) 
                    break;
                else if(w_num < r_num )
                {
                    ptr += w_num;
                    r_num -= w_num;
                }
            }
            if(w_num <= 0)
                break;
    }
    // if we get the file end
    if(feof(src))
    {
        fclose(src);
        fclose(dst);
        printf(" %s update(%s -> %s )ok\n", __func__, src_file, dst_file );
        return 0;
    }


Exit3:
    fclose(src);
Exit2:
    fclose(dst);
Exit1:
    return -1;
}

int update_ver(const char *file, const char *ver_key, char *ver)
{
    FILE *fp = NULL;
    char buf[512] = {};
    char *p = NULL;
    int result = -1;
    if(NULL == file || ver_key == NULL || NULL == ver)
        return -1;
    
    memset(ver, 0, sizeof(ver));
    fp = fopen(file, "r");
    if(fp == NULL)
    {
        fprintf(stderr,"fopen %s Error\n",file);
        return -2;
    }

    printf("%s file:%s open ok. key:%s\n", __func__,file, ver_key);
    memset(buf, 0, sizeof(buf));
    while((fgets(buf, sizeof(buf) -1, fp)) != NULL)
    {
        p = strstr(buf, ver_key);
        if(NULL == p)
        {
            memset(buf, 0, sizeof(buf));
            continue;
        }

        p +=  strlen(ver_key);
        printf("get new ver %s\n", p);
        sprintf(ver, "%s", p);
        result = 0;
        break; 
    }
    
    fclose(fp);

    if(result)
        return -3;

    printf("%supdate new ver ok\n", __func__);
    return 0;

}

int system_update(char *ver)
{
    //char *new_name[] = {"/DvrUI","/usr/lib/libsdk.so", "/autorun.sh","/etc/config.ini"};
    char *new_name = "/opt/update.tar";
    char *ver_file = "/tmp/config.ini";
    char *ver_key = "build-id=";
    
    if(access(fw_name, R_OK))
    {
        fprintf(stderr,"access %s Error\n",fw_name);
        return -1;
    }

    if(ls_cp_file(fw_name, new_name))
    {
        fprintf(stderr,"cp file Error\n");
        return -2;
    }

    if(system(". /update.sh"))
    {
        fprintf(stderr,"system update failed\n");
        return -3;
    }

    if(0 != update_ver(ver_file, ver_key, ver))
    {
        fprintf(stderr,"update new ver failed\n");
        return -4;
    }
    printf("%s  update success \n", __func__);

    return 0;
}


int ls_reboot(void)
{
    printf("sysReboot Start!\n");
    sync();
    return system("reboot");
}
#if 0
lock_file_rename(0, 2, "mp4", 0);
lock_file_rename(0, 2, "jpg", 1);
lock_file_rename(0, 3, "jpg", 0);

lock_file_rename(1, 4, "mp4", 0);
lock_file_rename(1, 4, "jpg", 1);
lock_file_rename(1, 5, "jpg", 0);
#endif

