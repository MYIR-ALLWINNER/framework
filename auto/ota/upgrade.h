#ifndef __MISC_MESSAGE_H__
#define __MISC_MESSAGE_H__

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mtd/mtd-user.h>
#include <assert.h>
#include <sys/ioctl.h>
#include "boot_head.h"
#include "dos.h"


#define DEATH(mess) { perror(mess); exit(errno); }

#define UBOOT_BUF_SIZE      (4 * 1024 * 1024)
#define MISC_LIMITED_SIZE   (4 * 1024)
#define MISC_DEVICE         "/dev/mmcblk1"

#define __DEF_DEBUG__
#ifdef __DEF_DEBUG__
#define LOGE(...) printf( __VA_ARGS__)
#else
#define LOGE(...)
#endif


#define CHECK_MISC_MESSAGE \
    ((sizeof(bootloader_message) > MISC_LIMIT_SIZE) ? -1 : 0)

#ifndef ROUND_UP	
//#define ROUND_UP(size, algin) ( (size + algin - 1) & ~(algin - 1))
#define ROUND_UP(size, algin)  (size)
#endif

#if defined(__linux__)
#  define RB_HALT_SYSTEM  0xcdef0123
#  define RB_ENABLE_CAD   0x89abcdef
#  define RB_DISABLE_CAD  0
#  define RB_POWER_OFF    0x4321fedc
#  define RB_AUTOBOOT     0x01234567
# elif defined(RB_HALT)
#  define RB_HALT_SYSTEM  RB_HALT
#endif

#define IMAGE_MAGIC			      "IMAGEWTY"
#define	IMAGE_HEAD_VERSION	      0x00000300
#define IMAGE_HEAD_SIZE     	  1024
#define IMAGE_ITEM_TABLE_SIZE     1024

#define MMCBLK0                   "/dev/mmcblk0"

#define PERM_ENABLE               "0"

#define MMC_SECT_SIZE             512
#define BOOT0_START               BOOT0_SDMMC_START_ADDR
#define BOOT0_BAKUP               BOOT0_SDMMC_BACKUP_START_ADDR  
#define UBOOT_START               UBOOT_START_SECTOR_IN_SDMMC
#define UBOOT_BAKUP               UBOOT_BACKUP_START_SECTOR_IN_SDMMC

#define STORAGE_BUFFER_SIZE       (256)
#define BOOT0_SIZE                (1024 * 1024)

#define SECTOR_SIZE               MMC_SECT_SIZE

#define IMAGE_ALIGN_SIZE		  0x400
#define HEAD_ATTR_NO_COMPRESS 	  0x4d    /* 1001101 */

#define CONFIG_MMC_LOGICAL_OFFSET   (20 * 1024 * 1024/512)

#ifndef TRUE  
#define TRUE                      1
#endif

#ifndef FALSE
#define FALSE                     0
#endif          

#pragma  pack (push,1)
typedef struct
{
	unsigned char magic[8];		/* IMAGE_MAGIC */
	unsigned int  version;		/* IMAGE_HEAD_VERSION */
	unsigned int  size;
	unsigned int  attr;
	unsigned int  imagever;
	unsigned int  lenLo;
	unsigned int  lenHi;
	unsigned int  align;		/* align with 1024 */
	unsigned int  pid;			/* PID  */
	unsigned int  vid;			/* VID  */
	unsigned int  hardwareid;
	unsigned int  firmwareid;
	unsigned int  itemattr;	
	unsigned int  itemsize;
	unsigned int  itemcount;
	unsigned int  itemoffset;
	unsigned int  imageattr;
	unsigned int  appendsize;
	unsigned int  appendoffsetLo;
	unsigned int  appendoffsetHi;
	unsigned char reserve[980];
}img_hdr_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagImageHeadAttr{
	unsigned int res:12;
	unsigned int len:8;
	unsigned int encode:7;		            /* HEAD_ATTR_NO_COMPRESS */
	unsigned int compress:5;
}ImageHeadAttr_t;
#pragma pack(pop)

#define	IMAGE_ITEM_VERSION	0x00000100
#define MAINTYPE_LEN		8
#define SUBTYPE_LEN			16
#define FILE_PATH			256
#define IMAGE_ITEM_RCSIZE   640


#pragma pack(push, 1)
typedef struct tag_ImageItem
{
	unsigned int  version;
	unsigned int  size;
	unsigned char mainType[MAINTYPE_LEN];
	unsigned char subType[SUBTYPE_LEN];
	unsigned int  attr;
	unsigned char name[FILE_PATH];
	unsigned int  datalenLo;
	unsigned int  datalenHi;
	unsigned int  filelenLo;
	unsigned int  filelenHi;
	unsigned int  offsetLo;
	unsigned int  offsetHi;
	unsigned char encryptID[64];
	unsigned int  checksum;
	unsigned char res[IMAGE_ITEM_RCSIZE];
}img_item_t;
#pragma pack(pop)

typedef struct
{
	img_hdr_t img_hdr;	
	img_item_t *item_tbl;
}img_hdl_t;

typedef struct{
	unsigned int index;	
	unsigned int reserved[3];
    /*long long pos;*/
}item_hdl_t;

#define     DOWNLOAD_MAP_NAME           "dlinfo.fex"
#define     SUNXI_MBR_NAME              "sunxi_mbr.fex"
/* MBR       */
#define     SUNXI_MBR_SIZE			    (16 * 1024)
#define     SUNXI_DL_SIZE				(16 * 1024)
#define   	SUNXI_MBR_MAGIC			    "softw411"
#define     SUNXI_MBR_MAX_PART_COUNT	120
#define     SUNXI_MBR_COPY_NUM          4 
#define     SUNXI_MBR_RESERVED          (SUNXI_MBR_SIZE - 32 - 4 - (SUNXI_MBR_MAX_PART_COUNT * sizeof(sunxi_partition)))
#define     SUNXI_DL_RESERVED           (SUNXI_DL_SIZE - 32 - (SUNXI_MBR_MAX_PART_COUNT * sizeof(dl_one_part_info)))

#define     SUNXI_NOLOCK                (0)
#define     SUNXI_LOCKING               (0xAA)
#define     SUNXI_RELOCKING             (0xA0)
#define     SUNXI_UNLOCK                (0xA5)

#define     EXTRACT_BUF_SIZE            (32 * 1024 * 1024)
/* partition information */
typedef struct sunxi_partition_t
{
	unsigned int addrhi;
	unsigned int addrlo;
	unsigned int lenhi;
	unsigned int lenlo;
	unsigned char classname[16];
	unsigned char name[16];
	unsigned int user_type;
	unsigned int keydata;
	unsigned int ro;
	unsigned int sig_verify;
	unsigned int sig_erase;
	unsigned int sig_value[4];
	unsigned int sig_pubkey;
	unsigned int sig_pbumode;
	unsigned char reserved2[36];
}__attribute__ ((packed))sunxi_partition;

/* mbr information */
typedef struct sunxi_mbr
{
	unsigned int crc32;
	unsigned int version;
	unsigned char magic[8];			        /* softw311" */
	unsigned int copy;
	unsigned int index;
	unsigned int PartCount;
	unsigned int stamp[1];
	sunxi_partition array[SUNXI_MBR_MAX_PART_COUNT];
	unsigned int lockflag;
	unsigned char res[SUNXI_MBR_RESERVED];
}__attribute__ ((packed)) sunxi_mbr_t;

typedef struct tag_one_part_info
{
	unsigned char name[16];
	unsigned int addrhi;
	unsigned int addrlo;
	unsigned int lenhi;
	unsigned int lenlo;
	unsigned char dl_filename[16];
	unsigned char vf_filename[16];
	unsigned int encrypt;
	unsigned int verify;
}__attribute__ ((packed)) dl_one_part_info;

typedef struct tag_download_info
{
	unsigned int crc32;
	unsigned int version;             /* 0x00000101 */
	unsigned char magic[8];			  /* "softw311" */
	unsigned int download_count; 
	unsigned int stamp[3];
	dl_one_part_info one_part_info[SUNXI_MBR_MAX_PART_COUNT];
	unsigned char res[SUNXI_DL_RESERVED];
}
__attribute__ ((packed)) sunxi_download_info;

typedef enum {
	sparse_none = 0xff,
	sparse_ok   = 0x5a,
}sparse_t;

#ifdef CONFIG_NAND_STORAGE
#define BLKREADBOOT0 _IO('v', 125)
#define BLKREADBOOT1 _IO('v', 126)
#define BLKBURNBOOT0 _IO('v', 127)
#define BLKBURNBOOT1 _IO('v', 128) 

typedef struct {
    void* buffer;
    long len;
} burn_param_t;
#endif 



#define BOOT0                     "boot0"
#define UBOOT                     "uboot"

#define SPARSE_FORMAT_TYPE_TOTAL_HEAD      0xff00
#define SPARSE_FORMAT_TYPE_CHUNK_HEAD      0xff01
#define SPARSE_FORMAT_TYPE_CHUNK_DATA      0xff02
#define SPARSE_FORMAT_TYPE_CHUNK_FILL_DATA 0xff03


#define CONFIG_SYS_REDUNDAND_ENVIRONMENT

#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
# define ENV_HEADER_SIZE	(sizeof(unsigned int) + 1)
#else
# define ENV_HEADER_SIZE	(sizeof(unsigned int))
#endif

#define CONFIG_ENV_SIZE     (128 *1024)
#define ENV_SIZE            (CONFIG_ENV_SIZE - ENV_HEADER_SIZE)

#define AU_ONCE_SECTOR_DEAL (EXTRACT_BUF_SIZE / 512)


typedef struct environment_s {
	unsigned int	crc;		/* CRC32 over data bytes	*/
#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
	unsigned char	flags;		/* active/obsolete flags	*/
#endif
	unsigned char	data[ENV_SIZE]; /* Environment data		*/
} env_t;

extern char bak_bootdev[64];

int sparse_main(char *src, char *dest, off_t offset);         
int update_part(const char *partitons, 
                  const char *path, loff_t offset, int verify);
int get_env(void);
int update_start(const char *path);
void replace_bootdev(const char *);

#endif /*__MISC_MESSAGE_H__*/
