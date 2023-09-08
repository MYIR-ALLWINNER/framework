#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "upgrade.h"
#include "ext4_utils.h"
#include "sparse_format.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef CONFIG_EMMC_STORAGE
#define BOOT0_MAIN  	(CONFIG_BYTES_PER_SECTOR * 16)
#define BOOT0_BAK   	(CONFIG_BYTES_PER_SECTOR * 256)
#define UBOOT_MAIN  	(CONFIG_BYTES_PER_SECTOR * 32800)
#define UBOOT_BAK   	(CONFIG_BYTES_PER_SECTOR * 24576)

#define AU_HEAD_BUFF 	(32 * 1024)
#endif

//#define crc_table(attr) _crc_table ## attr

#define cpu_to_le32(x)   (x)
#define le32_to_cpu(x)   (x)

#define tole(x)          cpu_to_le32(x)

extern int part_fd;
extern int total_write;

char bak_bootdev[64];

static img_hdl_t *img_hdl;
static sunxi_download_info dl_map;
static char *mbr_ptr;
static char fw_name[CONFIG_NAME_LEN];
static char boot_buf[UBOOT_BUF_SIZE];
static unsigned int crc_table[256];

static const unsigned crc_table_static[256] = {
	tole(0x00000000L), tole(0x77073096L), tole(0xee0e612cL), tole(0x990951baL),
	tole(0x076dc419L), tole(0x706af48fL), tole(0xe963a535L), tole(0x9e6495a3L),
	tole(0x0edb8832L), tole(0x79dcb8a4L), tole(0xe0d5e91eL), tole(0x97d2d988L),
	tole(0x09b64c2bL), tole(0x7eb17cbdL), tole(0xe7b82d07L), tole(0x90bf1d91L),
	tole(0x1db71064L), tole(0x6ab020f2L), tole(0xf3b97148L), tole(0x84be41deL),
	tole(0x1adad47dL), tole(0x6ddde4ebL), tole(0xf4d4b551L), tole(0x83d385c7L),
	tole(0x136c9856L), tole(0x646ba8c0L), tole(0xfd62f97aL), tole(0x8a65c9ecL),
	tole(0x14015c4fL), tole(0x63066cd9L), tole(0xfa0f3d63L), tole(0x8d080df5L),
	tole(0x3b6e20c8L), tole(0x4c69105eL), tole(0xd56041e4L), tole(0xa2677172L),
	tole(0x3c03e4d1L), tole(0x4b04d447L), tole(0xd20d85fdL), tole(0xa50ab56bL),
	tole(0x35b5a8faL), tole(0x42b2986cL), tole(0xdbbbc9d6L), tole(0xacbcf940L),
	tole(0x32d86ce3L), tole(0x45df5c75L), tole(0xdcd60dcfL), tole(0xabd13d59L),
	tole(0x26d930acL), tole(0x51de003aL), tole(0xc8d75180L), tole(0xbfd06116L),
	tole(0x21b4f4b5L), tole(0x56b3c423L), tole(0xcfba9599L), tole(0xb8bda50fL),
	tole(0x2802b89eL), tole(0x5f058808L), tole(0xc60cd9b2L), tole(0xb10be924L),
	tole(0x2f6f7c87L), tole(0x58684c11L), tole(0xc1611dabL), tole(0xb6662d3dL),
	tole(0x76dc4190L), tole(0x01db7106L), tole(0x98d220bcL), tole(0xefd5102aL),
	tole(0x71b18589L), tole(0x06b6b51fL), tole(0x9fbfe4a5L), tole(0xe8b8d433L),
	tole(0x7807c9a2L), tole(0x0f00f934L), tole(0x9609a88eL), tole(0xe10e9818L),
	tole(0x7f6a0dbbL), tole(0x086d3d2dL), tole(0x91646c97L), tole(0xe6635c01L),
	tole(0x6b6b51f4L), tole(0x1c6c6162L), tole(0x856530d8L), tole(0xf262004eL),
	tole(0x6c0695edL), tole(0x1b01a57bL), tole(0x8208f4c1L), tole(0xf50fc457L),
	tole(0x65b0d9c6L), tole(0x12b7e950L), tole(0x8bbeb8eaL), tole(0xfcb9887cL),
	tole(0x62dd1ddfL), tole(0x15da2d49L), tole(0x8cd37cf3L), tole(0xfbd44c65L),
	tole(0x4db26158L), tole(0x3ab551ceL), tole(0xa3bc0074L), tole(0xd4bb30e2L),
	tole(0x4adfa541L), tole(0x3dd895d7L), tole(0xa4d1c46dL), tole(0xd3d6f4fbL),
	tole(0x4369e96aL), tole(0x346ed9fcL), tole(0xad678846L), tole(0xda60b8d0L),
	tole(0x44042d73L), tole(0x33031de5L), tole(0xaa0a4c5fL), tole(0xdd0d7cc9L),
	tole(0x5005713cL), tole(0x270241aaL), tole(0xbe0b1010L), tole(0xc90c2086L),
	tole(0x5768b525L), tole(0x206f85b3L), tole(0xb966d409L), tole(0xce61e49fL),
	tole(0x5edef90eL), tole(0x29d9c998L), tole(0xb0d09822L), tole(0xc7d7a8b4L),
	tole(0x59b33d17L), tole(0x2eb40d81L), tole(0xb7bd5c3bL), tole(0xc0ba6cadL),
	tole(0xedb88320L), tole(0x9abfb3b6L), tole(0x03b6e20cL), tole(0x74b1d29aL),
	tole(0xead54739L), tole(0x9dd277afL), tole(0x04db2615L), tole(0x73dc1683L),
	tole(0xe3630b12L), tole(0x94643b84L), tole(0x0d6d6a3eL), tole(0x7a6a5aa8L),
	tole(0xe40ecf0bL), tole(0x9309ff9dL), tole(0x0a00ae27L), tole(0x7d079eb1L),
	tole(0xf00f9344L), tole(0x8708a3d2L), tole(0x1e01f268L), tole(0x6906c2feL),
	tole(0xf762575dL), tole(0x806567cbL), tole(0x196c3671L), tole(0x6e6b06e7L),
	tole(0xfed41b76L), tole(0x89d32be0L), tole(0x10da7a5aL), tole(0x67dd4accL),
	tole(0xf9b9df6fL), tole(0x8ebeeff9L), tole(0x17b7be43L), tole(0x60b08ed5L),
	tole(0xd6d6a3e8L), tole(0xa1d1937eL), tole(0x38d8c2c4L), tole(0x4fdff252L),
	tole(0xd1bb67f1L), tole(0xa6bc5767L), tole(0x3fb506ddL), tole(0x48b2364bL),
	tole(0xd80d2bdaL), tole(0xaf0a1b4cL), tole(0x36034af6L), tole(0x41047a60L),
	tole(0xdf60efc3L), tole(0xa867df55L), tole(0x316e8eefL), tole(0x4669be79L),
	tole(0xcb61b38cL), tole(0xbc66831aL), tole(0x256fd2a0L), tole(0x5268e236L),
	tole(0xcc0c7795L), tole(0xbb0b4703L), tole(0x220216b9L), tole(0x5505262fL),
	tole(0xc5ba3bbeL), tole(0xb2bd0b28L), tole(0x2bb45a92L), tole(0x5cb36a04L),
	tole(0xc2d7ffa7L), tole(0xb5d0cf31L), tole(0x2cd99e8bL), tole(0x5bdeae1dL),
	tole(0x9b64c2b0L), tole(0xec63f226L), tole(0x756aa39cL), tole(0x026d930aL),
	tole(0x9c0906a9L), tole(0xeb0e363fL), tole(0x72076785L), tole(0x05005713L),
	tole(0x95bf4a82L), tole(0xe2b87a14L), tole(0x7bb12baeL), tole(0x0cb61b38L),
	tole(0x92d28e9bL), tole(0xe5d5be0dL), tole(0x7cdcefb7L), tole(0x0bdbdf21L),
	tole(0x86d3d2d4L), tole(0xf1d4e242L), tole(0x68ddb3f8L), tole(0x1fda836eL),
	tole(0x81be16cdL), tole(0xf6b9265bL), tole(0x6fb077e1L), tole(0x18b74777L),
	tole(0x88085ae6L), tole(0xff0f6a70L), tole(0x66063bcaL), tole(0x11010b5cL),
	tole(0x8f659effL), tole(0xf862ae69L), tole(0x616bffd3L), tole(0x166ccf45L),
	tole(0xa00ae278L), tole(0xd70dd2eeL), tole(0x4e048354L), tole(0x3903b3c2L),
	tole(0xa7672661L), tole(0xd06016f7L), tole(0x4969474dL), tole(0x3e6e77dbL),
	tole(0xaed16a4aL), tole(0xd9d65adcL), tole(0x40df0b66L), tole(0x37d83bf0L),
	tole(0xa9bcae53L), tole(0xdebb9ec5L), tole(0x47b2cf7fL), tole(0x30b5ffe9L),
	tole(0xbdbdf21cL), tole(0xcabac28aL), tole(0x53b39330L), tole(0x24b4a3a6L),
	tole(0xbad03605L), tole(0xcdd70693L), tole(0x54de5729L), tole(0x23d967bfL),
	tole(0xb3667a2eL), tole(0xc4614ab8L), tole(0x5d681b02L), tole(0x2a6f2b94L),
	tole(0xb40bbe37L), tole(0xc30c8ea1L), tole(0x5a05df1bL), tole(0x2d02ef8dL)
};

/*
 *生成环境变量的crc校验值，否则修改了环境变量后，u-boot校验出错时，会用默认环境变量；
 */

#define DO_CRC(x) crc = tab[(crc ^ (x)) & 255] ^ (crc >> 8)
static unsigned int crc32_no_comp(unsigned int crc, const unsigned char *buf, 
                                          unsigned int len)
{
	const unsigned int *tab = crc_table_static;
	const unsigned int *b =(const unsigned int *)buf;
	size_t rem_len;

	if (!buf || !len)
		return ~0;
	unsigned int crc_tmp = crc;
	crc = cpu_to_le32(crc_tmp);
	/* Align it */
	if (((long)b) & 3 && len) {
		unsigned char *p = (unsigned char *)b;
		do {
			 DO_CRC(*p++);
		} while ((--len) && ((long)p)&3);
		b = (unsigned int *)p;
	}
	
	rem_len = len & 3;
	len = len >> 2;
	for (--b; len; --len) {
		/* load data 32 bits wide, xor data 32 bits wide. */
		crc ^= *++b; /* use pre increment for speed */
		DO_CRC(0);
		DO_CRC(0);
		DO_CRC(0);
		DO_CRC(0);
	}
	len = rem_len;
	/* And the last few bytes */
	if (len) {
		unsigned char *p = (unsigned char *)(b + 1) - 1;
		do {
			DO_CRC(*++p); /* use pre increment for speed */
		} while (--len);
	}
	
	return le32_to_cpu(crc);
}
#undef DO_CRC

static unsigned int uboot_crc32(unsigned int crc, const unsigned char *p, 
                                     unsigned int len)
{
	return crc32_no_comp(crc ^ 0xffffffffL, p, len) ^ 0xffffffffL;
}



static void init_crc_table(void)
{
	unsigned int c;
	unsigned int i, j;
	
	for (i = 0; i < 256; i++) {
		c = (unsigned int)i;
		for (j = 0; j < 8; j++) {
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[i] = c;
	}
}

static unsigned int crc32(unsigned int crc,unsigned char *buf, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++) {
		crc = crc_table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
	}
	return crc ;
}

static unsigned int generate_checksum(void *buffer, uint length)
{
    unsigned int crc = 0xffffffff; 

	return crc32(crc, buffer, length);
}

int verify_checksum(void *buffer, unsigned int length, unsigned int src_sum)
{
	unsigned int sum;
	sum = generate_checksum(buffer, length);

	if ( sum == src_sum )
		return 0;
	else
		return -1;
}

/*
 *将整数转换成字符串
 */
char* __attribute__((unused)) itoa(int num, char* str, int radix)
{
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned unum;
	int i=0,j,k;
 
	if(radix == 10 && num < 0){
		unum = (unsigned)-num;
		str[i++] = '-';
	} else 
		unum = (unsigned)num;
 
	do
	{
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
 
	} while(unum);
 
	str[i] = '\0';
 
	if (str[0] == '-') 
		k = 1;
	else 
		k = 0;
 
	char temp;
	for (j=k; j<=(i-1)/2; j++){
		temp = str[j];
		str[j] = str[i-1+k-j];
		str[i-1+k-j] = temp;
	}
 
	return str;
}


/*
 *解析固件基本信息
 */
static img_hdl_t *get_fw_info(const char *name)
{
	int ret, fd;
	img_hdl_t *img_hdl = NULL;
	int item_table_size;

	assert(name != NULL);
	fd = open(name, O_RDONLY);
	if (fd < 0){
		fprintf(stderr, "Open firmware failed or firmwae not exist:%s\n", name);
		return NULL;
	}
	
	img_hdl = (img_hdl_t *)malloc(sizeof(img_hdl_t));
	if (!img_hdl){
		close (fd);
		fprintf(stderr, "%s get memory failed!\n", __func__);
		return NULL;
	}
	memset(img_hdl, 0, sizeof(img_hdl_t));
	
	ret = read(fd, &img_hdl->img_hdr, 1024);
	if (ret <= 0){
		close(fd);
		fprintf(stderr, "read img informations failed!\n");
		return NULL;
	}
	
	if (memcmp(img_hdl->img_hdr.magic, IMAGE_MAGIC, 8)){
		close(fd);
		fprintf(stderr, "verify image magic err!\n");
        return NULL;
	}
	
	item_table_size = img_hdl->img_hdr.itemcount * sizeof(img_item_t);
	img_hdl->item_tbl = malloc(item_table_size);
	if (!img_hdl->item_tbl){
		close(fd);
		fprintf(stderr, "get img_hdr memory failed!\n");
		return NULL;
	}
	
	ret = read(fd, img_hdl->item_tbl, item_table_size);
	if (ret <= 0){
		close(fd);
		free(img_hdl);
		fprintf(stderr, "Reading item table failed!\n");
		return NULL;
	}

	close(fd);
	
	return img_hdl;	
}

/*
 *校验写入的固件
 */
static int __attribute__((unused)) verify_fw(const char *buf)
{
    return 0;
}


/*
 *获取固件的大小
 */
static inline size_t get_fw_size(const void *img)
{	
	return (((img_hdl_t *)img)->img_hdr.lenLo);
}

/*
 *获取下载分区信息
 */
static void *get_fw_items(const void *img, const char *major_type, const char *minor_stype)
{
	int i;
	img_hdl_t *img_hdl;
	item_hdl_t *pitem;
	
    assert(img);
	assert(major_type);
	assert(minor_stype);
	
	pitem = malloc(sizeof(item_hdl_t));
	if (!pitem){
		fprintf(stderr, "%s %d get memory failed!\n", __func__, __LINE__);
		return NULL;
	}
	img_hdl = (img_hdl_t *)img;
	
	pitem->index = ~0;
	
	for(i=0; i<img_hdl->img_hdr.itemcount; i++){
		if (!memcmp(img_hdl->item_tbl[i].subType, minor_stype, SUBTYPE_LEN)){
			pitem->index = i;
			return pitem;
		}
	}
	
	printf("%s %d find items failed!\n", __func__, __LINE__);
	free(pitem);
	return NULL;
}


static int read_item(const void *img, const item_hdl_t *pitem, void *dest, size_t size)
{
	size_t len;
	long ofs = 0;
	img_hdl_t *img_hdl = (img_hdl_t *)img;
	int fd;
	int ret;
	
	assert(img);
	assert(pitem);
	assert(dest);
	
	if (img_hdl->item_tbl[pitem->index].filelenHi){
		printf("%s %d Error items size \n", __func__, __LINE__);
		return -1;
	}
	
	len = (size_t)img_hdl->item_tbl[pitem->index].filelenLo;

	if(len > size){
		printf("%s %d Item too large, request size %d:!\n", __func__, __LINE__, (int)len);
		return -1;
	}

	ofs = img_hdl->item_tbl[pitem->index].offsetLo;
	fd = open(fw_name, O_RDONLY);
	if (fd < 0){
		fprintf(stderr, "%s %d Open file %s failed\n", __func__, __LINE__, fw_name);
		return -1;
	}
	
	lseek(fd, ofs, SEEK_SET);
	ret = read(fd, dest, len);
	if (ret <= 0){
		fprintf(stderr, "%s %d Read failed!\n", __func__, __LINE__);
		close(fd);
		return -1;
	}
	
	close(fd);
	return len;
}

#define HEADR_READ_SIZE  (1UL << 20)
static sparse_t __attribute__((unused)) detect_sparse(off_t offset)
{
	int fd;
	sparse_header_t *sparse_header;
	u8 buf[HEADR_READ_SIZE];

	fd = open(fw_name, O_RDONLY);
	if (fd < 0){
		fprintf(stderr, "open firmware failed\n");
		return sparse_none;
	}

	lseek(fd, offset, SEEK_SET);
	if (read(fd, buf, HEADR_READ_SIZE) != HEADR_READ_SIZE){
		fprintf(stderr, "can not read information from firmware %d position\n",
			    (int)offset);
		close(fd);
		return sparse_none;
	}
	close(fd);

	sparse_header = (sparse_header_t *)buf;
	if (sparse_header->magic != SPARSE_HEADER_MAGIC)
		return sparse_none;
	else
		return sparse_ok;
}
#undef HEADR_READ_SIZE

/*
 * 烧录除了boot0,uboot之外的其他分区 
 */
static int burn_normal(const void *img, const item_hdl_t *pitem, const char *dl)
{
	int ret, fdr, fdw;
	unsigned int size = 0, part_size;
	char *name, __attribute__((unused))*part;
	long ofs = 0;
	img_hdl_t *img_hdl = (img_hdl_t *)img;
	unsigned char *buf;
	const dl_one_part_info *dl_info = (const dl_one_part_info *)dl;
	
	if (!img || !pitem || !dl || !img_hdl || !dl_info){
		printf("%s invalid argument!\n", __func__);
		return -1;
	}

	ret = -1;
	name = (char *)dl_info->name;
	size = img_hdl->item_tbl[pitem->index].filelenLo;		
	part_size = dl_info->lenlo << 9;
	if (size > part_size){
		printf("part data exceed part size!\n");
		return -1;
	}

	part = getenv(name);
	if (!part || !part[0]){
		printf("failed to get partitons from env varable!\n");
		return -1;
	}
	
	ofs = img_hdl->item_tbl[pitem->index].offsetLo;
	if (detect_sparse(ofs) == sparse_ok){
		printf("detected sparese format\n");
		if (!strncmp(name, "rootfs", strlen("rootfs")))
			ret = sparse_main(fw_name, bak_bootdev, (off_t)ofs);
		else
			ret = sparse_main(fw_name, part, (off_t)ofs);
	} else {
		fdr = open(fw_name, O_RDONLY);
		if (fdr < 0){
			fprintf(stderr, "open file %s failed!\n", fw_name);
			return -1;
		}
		
		buf = malloc(EXTRACT_BUF_SIZE);
		if (!buf){
			fprintf(stderr, "can not allocation memory!\n");
			return -1;
		}
		
		fdw = open(part, O_WRONLY | O_TRUNC, 0664);
		if (fdw < 0){
			free(buf);
			close(fdr);
			fprintf(stderr, "can not allocation memory!\n");
			return -1;
		}

		lseek(fdr, ofs, SEEK_SET);

		ret = -1;
		if (read(fdr, buf, size) == size){
			if (write(fdw, buf, size) == size)
				ret = 0;
		}
		free(buf);
		close(fdr);
		close(fdw);
	}

	return ret;
}

static int show_partitions(const void *data)
{
	int i;
	const sunxi_download_info *info;
	const dl_one_part_info *part_info;
	char buffer[32];
	
	assert(data);
	
	info = (const sunxi_download_info *)data;
	printf("*************IMG MAP DUMP************\n");
	printf("total IMG part %u\n", info->download_count);
	printf("\n");
	for(part_info = info->one_part_info, i=0; i<info->download_count; i++, part_info++)
	{
		memset(buffer, 0, 32);
		memcpy(buffer, part_info->name, 16);
		printf("IMG part[%d] name          :%s\n", i, buffer);
		memset(buffer, 0, 32);
		memcpy(buffer, part_info->dl_filename, 16);
		printf("IMG part[%d] IMG file      :%s\n", i, buffer);
		memset(buffer, 0, 32);
		memcpy(buffer, part_info->vf_filename, 16);
		printf("IMG part[%d] verify file   :%s\n", i, buffer);
		printf("IMG part[%d] lenlo         :0x%x\n", i, part_info->lenlo);
		printf("IMG part[%d] addrlo        :0x%x\n", i, part_info->addrlo);
		printf("IMG part[%d] encrypt       :0x%x\n", i, part_info->encrypt);
		printf("IMG part[%d] verify        :0x%x\n", i, part_info->verify);
		printf("\n");
	}
	
    return 0;
}

static int get_fw_map(const void *img, sunxi_download_info *map_info)
{
	int ret;
	item_hdl_t *pitem = NULL;
    assert(map_info);
	
	pitem = get_fw_items(img, "12345678", "1234567890DLINFO");
	assert(pitem);
	
	ret = read_item(img, pitem, (void *)map_info, sizeof(sunxi_download_info));
	if (ret > 0){
		sunxi_download_info *info;
		info = (sunxi_download_info *)map_info;
		if(memcmp(info->magic, SUNXI_MBR_MAGIC, strlen(SUNXI_MBR_MAGIC)))
		    ret = -1;
	}else{
		ret = -1;
	}
	if (pitem)
		free((void *)pitem);
	return ret;
}

static int show_mbr_info(const void *data)
{
	sunxi_mbr_t *mbr = (sunxi_mbr_t *)data;
	sunxi_partition *part_info;
	unsigned int i;
	char buffer[32];

	printf("*************MBR DUMP***************\n");
	printf("total mbr part %u\n", mbr->PartCount);
	printf("\n");
	for(part_info = mbr->array, i=0; i<mbr->PartCount;i++, part_info++)
	{
		memset(buffer, 0, 32);
		memcpy(buffer, part_info->name, 16);
		printf("part[%u] name      :%s\n", i, buffer);
		memset(buffer, 0, 32);
		memcpy(buffer, part_info->classname, 16);
		printf("part[%u] classname :%s\n", i, buffer);
		printf("part[%u] addrlo    :0x%x\n", i, part_info->addrlo);
		printf("part[%u] lenlo     :0x%x\n", i, part_info->lenlo);
		printf("part[%u] user_type :%u\n", i, part_info->user_type);
		printf("part[%u] keydata   :%u\n", i, part_info->keydata);
		printf("part[%u] ro        :%u\n", i, part_info->ro);
		printf("\n");
	}
	
    return 0;
}

static int get_fw_mbr(const void *img, void **data)
{
	int ret;
	char *buf;
	item_hdl_t *pitem = NULL;
	int mbr_cnt = SUNXI_MBR_COPY_NUM;
	
    assert(img);
	
	pitem = get_fw_items(img, "12345678", "1234567890___MBR");
	assert(pitem);
	buf = malloc(1 << 20);
	if (!buf){
		fprintf(stderr, "allocate memory failed!\n");
		return -1;
	}
    
	ret = read_item(img, pitem, buf, sizeof(sunxi_mbr_t) * mbr_cnt);
	if (ret > 0){
		sunxi_mbr_t *mbr = (sunxi_mbr_t *)buf;
		if(!memcmp(mbr->magic, SUNXI_MBR_MAGIC, strlen(SUNXI_MBR_MAGIC))){
		    *data = buf;
		}else
			ret = -1;
	}else{
		ret = -1;
	}
	
	if (pitem){
		free((void *)pitem);
	}
	return ret;
}

static int update_boot0info(void *inbuf, void *outbuf, int buf_size)
{
    assert(inbuf);
	assert(outbuf);

	unsigned char *src, *dest;

	if (buf_size < (sizeof(struct boot_sdmmc_private_info_t))){
		printf("wrong input param\n ");
		return -1;
	}

	src = (unsigned char*)inbuf;
	dest = (unsigned char*)outbuf;

	src += SDMMC_PRIV_INFO_ADDR_OFFSET;
	dest += SDMMC_PRIV_INFO_ADDR_OFFSET;
    memcpy((void *)dest, (void *)src, sizeof(struct boot_sdmmc_private_info_t));

	return 0;
}

static int gen_boot0checksum(void *data)
{
	unsigned int sum, *psum;
	unsigned int len, loop, i;
	standard_boot_file_head_t *head_p;
	unsigned int *buf;

	head_p = (standard_boot_file_head_t *)data;

	psum = &head_p->check_sum ;
	len = head_p->length;

	if (len & 0x3){
		printf("data len must 4-byte-aligned! \n");
		return -1;
	}

	buf = (unsigned int *)data;
	*psum = STAMP_VALUE;
	loop = len >> 2;
	sum = 0;
	for(i=0;  i<loop;  i++ )
		sum += buf[i];
	*psum = sum;

	return 0;

}

static int update_boot0(char *buf, int size)
{
    assert(buf);
	
    unsigned char old[BOOT0_SIZE], *new;
	boot0_file_head_t *oldboot0;
	boot0_file_head_t *newboot0;
	int fd;
	int ret;
	
    fd = open(MMCBLK0, O_RDONLY);
	if (fd < 0){
		fprintf(stderr, "open old boot0 partitions failed! \n");
		return -1;
	}
	lseek(fd, 16 * 512, SEEK_SET);
	
	ret = read(fd, old, size);
	if (ret != size){
		fprintf(stderr, "read old boot0 failed! \n");
		close(fd);
		return -1;
	}
	close(fd);

	new = (unsigned char *)buf;
	oldboot0 = (boot0_file_head_t *)&old[0];
	newboot0 = (boot0_file_head_t *)&new[0];
	ret = update_boot0info((void *)oldboot0->prvt_head.storage_data, 
		             (void *)newboot0->prvt_head.storage_data,
		             STORAGE_BUFFER_SIZE);
	if (!ret){
		ret = gen_boot0checksum((void *)&new[0]);

		if (ret < 0)
			return ret;
	}
	
	return ret;
}

static int read_part(const char *part, off_t offset, char *out, size_t size)
{
    int fd, ret, len;

	assert(part);
	assert(out);
	assert(size);

	fd = open(part, O_RDONLY);
	if (fd < 0){
		fprintf(stderr, "Open partitions %s failed!\n", part);
        return -1;
	}
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	lseek(fd, offset, SEEK_CUR);

	if (len < size)
		size = len;
	
	ret = read(fd, out, size);
	close(fd);

    return ret;
}

static int boot_verify(int boot_type, unsigned int size)
{
	int ret = -1;
	unsigned int crc = 0;
	char *buf = boot_buf;

	if (size <= 0)
		return 0;
	
	memset(buf, 0, size);

	init_crc_table();

	/*check main partitions*/
	if (boot_type == 1)
		ret = read_part(MMCBLK0, BOOT0_MAIN, buf, (size_t)size);
	else if (boot_type == 2)
		ret = read_part(MMCBLK0, UBOOT_MAIN, buf, (size_t)size);
	if (ret == size) {
		crc = generate_checksum(buf, ret);
		ret = verify_checksum(buf, size, crc);
		if(ret)
			goto crc_err;
	}

	/*check bak partitions*/
	memset(buf, 0, size);
	if (boot_type == 1)
		ret = read_part(MMCBLK0, BOOT0_BAK, buf, (size_t)size);
	else if (boot_type == 2)
		ret = read_part(MMCBLK0, UBOOT_BAK, buf, (size_t)size);
	if (ret == size) {
		crc = generate_checksum(buf, ret);
		ret = verify_checksum(buf, size, crc);
		if(ret)
			goto crc_err;
	} 
	return 0;

crc_err:
	printf("ERROR crc data for boot partitions!\n");
	return -1;
}

/**
 *烧录boot0和uboot分区
 */
static int burn_boot(void *buf, int size, int boot_type)
{
	int fd, ret;
	
#ifdef CONFIG_NAND_STORAGE
	burn_param_t cookie;
	
	cookie.buffer = buf;
	cookie.len = size;
	
	ret = -1;	
	fd = open("dev/nand0", O_RDWR);
	if (fd > 0)
		if (boot_type == 1)
			ret = ioctl(fd1, BLKBURNBOOT0, (unsigned long)&cookie);
		else if (boot_type == 2)
			ret = ioctl(fd1, BLKBURNBOOT1, (unsigned long)&cookie);
		else{
			ret = 0;
			goto err_out;
		}
		
	if (ret)
		printf("burnNandBoot0 failed ! errno is %d : %s\n", errno, strerror(errno));
	else
		printf("burnNandBoot0 succeed!\n");
	
	close(fd);
	ret = 0;
#else
	fd = -1;

	fd = open(MMCBLK0, O_RDWR | O_SYNC);
	if (fd <= 0){
		fprintf(stderr, "Failed to open partitions %s\n", MMCBLK0);
		return -1;
	}

	if (boot_type == 1){
		lseek(fd, BOOT0_MAIN, SEEK_SET);
		ret = write(fd, buf, size);
		if (ret == size){
			lseek(fd, 0, SEEK_SET);
			lseek(fd, BOOT0_BAK, SEEK_SET);
			ret = write(fd, buf, size);
			if(ret != size)
				goto err_out;
		}else
			goto err_out;
		
	}else if (boot_type == 1){
		lseek(fd, UBOOT_MAIN, SEEK_SET);
		ret = write(fd, buf, size);
		if (ret == size){
			lseek(fd, 0, SEEK_SET);
			lseek(fd, UBOOT_BAK, SEEK_SET);
			ret = write(fd, buf, size);
			if(ret != size)
				goto err_out;
		}else
			goto err_out;
	}

	ret = boot_verify(boot_type, size);
#endif

err_out:
	close(fd);
	return ret;	
}


/*
 *提取boot0、u-boot，并烧录到eMMC，NAND等
 */
static int extract_boot(const void *data, const void *name)
{
	int ret, size;
	item_hdl_t *pitem = NULL;
	char *buf;
	int boot_type = -1;

	assert(data);
	assert(name);

	buf = boot_buf;

    if (!strncmp(name, "boot0", 5)){
		boot_type = 1;
		pitem = get_fw_items(data, "12345678", "1234567890BOOT_0");
    }else if (!strncmp(name, "uboot", 5)){
        boot_type = 2;
	    pitem = get_fw_items(data, "12345678", "BOOTPKG-00000000");
    }else{
		printf("unkonwn partitions %s\n", (char *)name);
		return -1;
    }
	if (!pitem){
		printf("get uboot items failed! \n");
		return -1;
	}
	
	ret = read_item(data, pitem, buf, UBOOT_BUF_SIZE);
    if (ret < 0)
		return -1;

    size = ret;
    if (boot_type == 1){
		boot0_file_head_t  *head  = (boot0_file_head_t *)buf;
		if(strncmp((const char *)head->boot_head.magic, 
			BOOT0_MAGIC, strlen(BOOT0_MAGIC))){
			printf("boot0 Magic error!\n");
			free(buf);
			return -1;

		}
		if (update_boot0(buf, size) < 0)
			return -1;
    }
	else if (boot_type == 2){
		sbrom_toc1_head_info_t *toc1 = (sbrom_toc1_head_info_t *)buf;
		if(toc1->magic != TOC_MAIN_INFO_MAGIC){
			printf("uboot pkg magic error!\n");
			return -1;
		}
    }
	else{
		printf("unkown boot type!\n");
		return -1;

    }

	ret = burn_boot(buf, size, boot_type );

	return ret;
}


static int __attribute__((unused))extract_udisk(const void *img, void **data)
{
	return 0;
}


/*
 *提取并烧录普通分区
 */
static int extract_normal(const void *data, const dl_one_part_info *part_info)
{
    int ret = -1;
	int fd = -1;
	item_hdl_t *pitem = NULL;
	
    fd = open(fw_name, O_RDONLY);
	if (fd > 0){
		pitem = get_fw_items(data, "RFSFAT16", (char *)part_info->dl_filename);
		ret = burn_normal(data, pitem, (const char *)part_info);
		if (pitem)
			free((void *)pitem);

		close(fd);
	}
	
	return ret;
}

static inline void set_fw_name(const char *name, char *dest)
{
	if (name && name[0] && dest)
		strncpy(dest, name, CONFIG_NAME_LEN);
}

static int get_img_info(img_hdl_t **out)
{
	img_hdl_t *img_hdl;

	assert(out);
	img_hdl = get_fw_info(fw_name);
	if (img_hdl){
	    *out = img_hdl;	
	    return 0;
	}else
	    return -1;
}


static inline int sunxi_sprite_size()
{
    return 0;
}

static int __attribute__((unused))write_user_mbr(const void *data)
{
    int fd;
    int ret;
	int size = sizeof(sunxi_mbr_t) * SUNXI_MBR_COPY_NUM;
	
	fd = open(MMCBLK0, O_RDWR);
	if (fd < 0){
		fprintf(stderr, "functions %s open %s partitions failed\n", __func__, MMCBLK0);
		return -1;
	}
	lseek(fd, CONFIG_MMC_LOGICAL_OFFSET, SEEK_CUR);
	ret = write(fd, data, size);
	fsync(fd);
	close(fd);

    printf("user mbr update success!\n");
	return ret == size ? 0 : -1;
}

static int __attribute__((unused))write_system_mbr(const void *data)
{
    int fd;
    char buf[SECTOR_SIZE];
	mbr_sys_t *sys_mbr;
	int i;
	int ret;
	int sectors;
	int unusd_sectors;

	const sunxi_mbr_t *mbr = (const sunxi_mbr_t *)data;
    assert(data);

	fd = open(MMCBLK0, O_RDWR);
	if (fd < 0){
		fprintf(stderr, "functions %s open %s partitions failed\n", __func__, MMCBLK0);
		return -1;
	}
	
	lseek(fd, SECTOR_SIZE, SEEK_SET);
	sectors = 0;
	for (i=1; i<mbr->PartCount-1; i++)
	{
		memset(buf, 0, SECTOR_SIZE);
		sys_mbr = (mbr_sys_t *)buf;

		sectors += mbr->array[i].lenlo;

		sys_mbr->part_info[0].part_type = 0x83;
		sys_mbr->part_info[0].start_sectorl = 
			    ((mbr->array[i].addrlo - i + 20 * 1024 * 1024/512 ) & 0x0000ffff) >> 0;
		sys_mbr->part_info[0].start_sectorh = 
			    ((mbr->array[i].addrlo - i + 20 * 1024 * 1024/512 ) & 0xffff0000) >> 16;
		sys_mbr->part_info[0].total_sectorsl = ( mbr->array[i].lenlo & 0x0000ffff) >> 0;
		sys_mbr->part_info[0].total_sectorsh = ( mbr->array[i].lenlo & 0xffff0000) >> 16;

		if (i != mbr->PartCount-2)
		{
			sys_mbr->part_info[1].part_type = 0x05;
			sys_mbr->part_info[1].start_sectorl = i;
			sys_mbr->part_info[1].start_sectorh = 0;
			sys_mbr->part_info[1].total_sectorsl = (mbr->array[i].lenlo  & 0x0000ffff);
			sys_mbr->part_info[1].total_sectorsh = (mbr->array[i].lenlo  & 0xffff0000) >> 16;
		}

		sys_mbr->end_flag = 0xAA55;
		if (write(fd, buf, SECTOR_SIZE) != SECTOR_SIZE)
		{
			fprintf(stderr, "write system mbr %d failed\n", i);
			ret = -1;
			goto err_ret;
		}
		fsync(fd);
	}
	memset(buf, 0, 512);
	sys_mbr = (mbr_sys_t *)buf;

	unusd_sectors = sunxi_sprite_size() - 20 * 1024 * 1024/512 - sectors;
	sys_mbr->part_info[0].indicator = 0x80;
	sys_mbr->part_info[0].part_type = 0x0B;
	sys_mbr->part_info[0].start_sectorl  = 
		    ((mbr->array[mbr->PartCount-1].addrlo + 20 * 1024 * 1024/512 ) & 0x0000ffff) >> 0;
	sys_mbr->part_info[0].start_sectorh  = 
		    ((mbr->array[mbr->PartCount-1].addrlo + 20 * 1024 * 1024/512 ) & 0xffff0000) >> 16;
	sys_mbr->part_info[0].total_sectorsl = ( unusd_sectors & 0x0000ffff) >> 0;
	sys_mbr->part_info[0].total_sectorsh = ( unusd_sectors & 0xffff0000) >> 16;

	sys_mbr->part_info[1].part_type = 0x06;
	sys_mbr->part_info[1].start_sectorl  = 
		    ((mbr->array[0].addrlo + 20 * 1024 * 1024/512) & 0x0000ffff) >> 0;
	sys_mbr->part_info[1].start_sectorh  = 
		    ((mbr->array[0].addrlo + 20 * 1024 * 1024/512) & 0xffff0000) >> 16;
	sys_mbr->part_info[1].total_sectorsl = (mbr->array[0].lenlo  & 0x0000ffff) >> 0;
	sys_mbr->part_info[1].total_sectorsh = (mbr->array[0].lenlo  & 0xffff0000) >> 16;

	sys_mbr->part_info[2].part_type = 0x05;
	sys_mbr->part_info[2].start_sectorl  = 1;
	sys_mbr->part_info[2].start_sectorh  = 0;
	sys_mbr->part_info[2].total_sectorsl = (sectors & 0x0000ffff) >> 0;
	sys_mbr->part_info[2].total_sectorsh = (sectors & 0xffff0000) >> 16;
	sys_mbr->end_flag = 0xAA55;

    i = 0;
	lseek(fd, (off_t)i, SEEK_SET);
	if (write(fd, buf, SECTOR_SIZE) != SECTOR_SIZE){
		fprintf(stderr, "write system mbr %d failed\n", i);
		ret = -1;
		goto err_ret;
	}

	printf("system mbr update success!\n");
	ret = 0;
	fsync(fd);
err_ret:
	close(fd);
	return ret;
}

int update_start(const char *name)
{
	int ret, i;
	size_t size;
	struct stat st;
	dl_one_part_info *one_part;

	set_fw_name(name, fw_name);

	if (fw_name[0] == '\0') {
		printf("Invalid firemware name!\n");
		return -1;
	}
	
	ret = get_img_info(&img_hdl);
	if (ret < 0)
		return ret;
		
	size = get_fw_size((void *)img_hdl);
	lstat(fw_name, &st);
	if (st.st_size != size) {
		printf("firmware size error, recoder size:%d, really size%d\n",
			   (int)size, (int)(st.st_size));
		return -1;
	}
	
	ret = get_fw_map(img_hdl, &dl_map);
	if (ret < 0) {
		printf("fetch firmware image map failed!\n");
		return ret;
	}
	show_partitions((const void *)&dl_map);
	
	ret = get_fw_mbr((const void *)img_hdl, (void **)&mbr_ptr);
	if (ret < 0) {
		printf("fetch firmware MBR failed!\n");
		return ret;
	}
	show_mbr_info(mbr_ptr);

	for (one_part=dl_map.one_part_info, i=0; 
	     i < dl_map.download_count; i++, one_part++){
		if (!strncmp("UDISK", (char *)one_part->name,
			strlen("UDISK"))){
			continue;
		}else if (!strncmp("sysrecovery", (char *)one_part->name,
				  strlen("sysrecovery"))) {
			continue;
		}else if (!strncmp("private", (char *)one_part->name,
				  strlen("private"))) {
			continue;
		} else{
			printf("extracting %s partitions\n", (char *)one_part->name);
			ret = extract_normal(img_hdl, one_part);
			if (ret) {
				printf("extract && write normal partitions failed \n");
				return ret;
			}
		}
	}

	ret = extract_boot(img_hdl, BOOT0);
	if (ret) {
		printf("extract && write boot0 failed \n");
		return ret;
	}
	ret = extract_boot(img_hdl, UBOOT);
	if (ret) {
		printf("extract && write uboot failed \n");
		return ret;
	}

#ifdef CONFIG_UPDATE_MBR
	write_user_mbr(mbr_ptr);
	write_system_mbr(mbr_ptr);
#endif

	if (img_hdl){
		free(img_hdl);
		img_hdl = NULL;
	}

	if (mbr_ptr){
		free(mbr_ptr);
		mbr_ptr = NULL;
	}

	if (!ret)
		printf ("system OTA successfull!\n");
	else
		printf ("system OTA failed!\n");
    return ret;
}

static char* memstr(char* full_data, int full_data_len, char* substr)
{
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
        return NULL;
    }

    if (*substr == '\0') {
        return NULL;
    }

    int sublen = strlen(substr);

    int i;
    char* cur = full_data;
    int last_possible = full_data_len - sublen + 1;
    for (i = 0; i < last_possible; i++) {
        if (*cur == *substr) 
            if (!memcmp(cur, substr, sublen)) 
                return cur;
        cur++;
    }

    return NULL;
}


void replace_bootdev(const char *env)
{
	int fd, ret;
	char *env_part, temp[64] = {0}, 
		  env_buf[ALIGN(CONFIG_ENV_SIZE, 512)] = {0},
		  new_part[64] = {0};
	env_t *envp;

	memset(&temp[0], 0, sizeof(temp));
	memset(&env_buf[0], 0, sizeof(env_buf));
	
	env_part = getenv(env);
	if (strncmp(env_part, "/dev/", 5))
		snprintf(temp, sizeof(temp), "/dev/%s", env_part);
	else
		strncpy(temp, env_part, sizeof(temp));

	printf("env partitions %s\n", env_part);

	fd = -1;
	fd = open(temp, O_RDWR);
	if (fd > 0){
		ret = read(fd, env_buf, sizeof(env_buf));
		if (ret == sizeof(env_buf)){
			char *start;

			start = memstr(env_buf, sizeof(env_buf), "mmc_root=/dev/");		
			snprintf(new_part, sizeof(new_part), "mmc_root=%s", bak_bootdev);
			if (start){
				strncpy(start, new_part, strlen(new_part));
			    envp = (env_t *)env_buf;
				envp->crc = uboot_crc32(0, envp->data, ENV_SIZE);
				printf("##### CRC: 0x%x\n", envp->crc);
				lseek(fd, 0, SEEK_SET);
				ret = write(fd, env_buf, sizeof(env_buf));
				if (ret == sizeof(env_buf))
					fsync(fd);
			}
		}

		close(fd);
	}
}


