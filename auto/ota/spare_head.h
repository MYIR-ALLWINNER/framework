#ifndef __SPARE_HEAD_H__
#define __SPARE_HEAD_H__

#define WORK_MODE_PRODUCT           (1<<4)
#define WORK_MODE_UPDATE            (1<<5)

#define WORK_MODE_BOOT			    0x00	
#define WORK_MODE_USB_PRODUCT	    0x10
#define WORK_MODE_CARD_PRODUCT	    0x11
#define WORK_MODE_USB_DEBUG	        0x12 
#define WORK_MODE_SPRITE_RECOVERY   0x13
#define WORK_MODE_CARD_UPDATE	    0x14	/* pdate firmware from sdcard */
#define WORK_MODE_USB_UPDATE	    0x20
#define WORK_MODE_OUTER_UPDATE	    0x21

#define WORK_MODE_USB_TOOL_PRODUCT	0x04
#define WORK_MODE_USB_TOOL_UPDATE	0x08
#define WORK_MODE_ERASE_KEY			0x20

#define UBOOT_MAGIC				    "uboot"
#define STAMP_VALUE                 0x5F0A6C39
#define ALIGN_SIZE				    (16 * 1024)
#define MAGIC_SIZE                  8
#define STORAGE_BUFFER_SIZE         (256)

#define SUNXI_UPDATE_NEXT_ACTION_NORMAL			(1)
#define SUNXI_UPDATE_NEXT_ACTION_REBOOT			(2)
#define SUNXI_UPDATE_NEXT_ACTION_SHUTDOWN		(3)
#define SUNXI_UPDATE_NEXT_ACTION_REUPDATE		(4)
#define SUNXI_UPDATE_NEXT_ACTION_BOOT			(5)
#define SUNXI_UPDATA_NEXT_ACTION_SPRITE_TEST    (6)

#define SUNXI_VBUS_UNKNOWN                      (0)
#define SUNXI_VBUS_EXIST                        (1)
#define SUNXI_VBUS_NOT_EXIST                    (2)

#define BOOT0_SDMMC_START_ADDR                  (16)
#define BOOT0_SDMMC_BACKUP_START_ADDR           (256)

#define BOOT0_EMMC3_START_ADDR                  (384)
#define BOOT0_EMMC3_BACKUP_START_ADDR           (512)


#define UBOOT_START_SECTOR_IN_SDMMC             (32800)
#define UBOOT_BACKUP_START_SECTOR_IN_SDMMC      (24576)


#define SUNXI_NORMAL_MODE                            0
#define SUNXI_SECURE_MODE_WITH_SECUREOS              1
#define SUNXI_SECURE_MODE_NO_SECUREOS                2

typedef enum _SUNXI_BOOT_FILE_MODE
{
	SUNXI_BOOT_FILE_NORMAL =0,
	SUNXI_BOOT_FILE_TOC = 1,
	SUNXI_BOOT_FILE_RES0 = 2,
	SUNXI_BOOT_FILE_RES1 = 3,
	SUNXI_BOOT_FILE_PKG = 4
}SUNXI_BOOT_FILE_MODE;



#define   BOOT_FROM_SD0     0
#define   BOOT_FROM_SD2     2
#define   BOOT_FROM_NFC     1
#define   BOOT_FROM_SPI     3

#if 0
//#define	TOC_MAIN_INFO_STATUS_ENCRYP_NOT_USED	0x00
//#define	TOC_MAIN_INFO_STATUS_ENCRYP_SSK		0x01
//#define	TOC_MAIN_INFO_STATUS_ENCRYP_BSSK		0x02
#endif
#define SUNXI_SECURE_MODE_USE_SEC_MONITOR             1

#define	TOC_ITEM_ENTRY_STATUS_ENCRYP_NOT_USED	0x00
#define	TOC_ITEM_ENTRY_STATUS_ENCRYP_USED		0x01

#define	TOC_ITEM_ENTRY_TYPE_NULL				0x00
#define	TOC_ITEM_ENTRY_TYPE_KEY_CERTIF			0x01
#define	TOC_ITEM_ENTRY_TYPE_BIN_CERTIF			0x02
#define	TOC_ITEM_ENTRY_TYPE_BIN     			0x03
#define TOC_ITEM_ENTRY_TYPE_LOGO                0x04

typedef struct _normal_gpio_cfg
{
    char port;                      
    char port_num;                 
    char mul_sel;                   
    char pull;                       
    char drv_level;                 
    char data;                     
    char reserved[2];                
}
normal_gpio_cfg;

typedef struct _special_gpio_cfg
{
	unsigned char port;				
	unsigned char port_num;			
	char mul_sel;			
	char data;				
}special_gpio_cfg;

typedef struct sdcard_spare_info_t
{
	int card_no[4];                 
	int speed_mode[4];                
	int line_sel[4];                  
	int line_count[4];               
}
sdcard_spare_info;

typedef enum
{
	STORAGE_NAND =0,
	STORAGE_SD,
	STORAGE_EMMC,
	STORAGE_NOR,
    STORAGE_EMMC3
}SUNXI_BOOT_STORAGE;

#endif