/*
* ota config files
*/
#undef CONFIG_UPDATE_MBR
#undef CONFIG_NAND_STORAGE
#undef CONFIG_BURN_ROOTFS

#define CONFIG_BURN_ROOTFS

#define CONFIG_EMMC_STORAGE
#define CONFIG_NAME_LEN                   64
#define CONFIG_BYTES_PER_SECTOR			  512

#define CONFIG_OUT_DEV_PART

#define ROOTS_BAK                         "/dev/mmcblk0p8"
