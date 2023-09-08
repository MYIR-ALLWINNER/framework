/*
 * (C) Copyright 2012
 *     wangflord@allwinnertech.com
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 */

#ifndef __DOS_PART_H_
#define __DOS_PART_H_


#pragma pack(push, 1)
typedef struct
{
	char 				indicator;	
	char				start_head;
	short				start_sector:6;
	short				start_cylinder:10;
	char				part_type;		
	char				end_head;
	short				end_sector:6;
	short				end_cylinder:10;
	//int					start_sectors;
	//int					total_sectors;
	short				start_sectorl;
	short				start_sectorh;
	short				total_sectorsl;
	short				total_sectorsh;
}part_info_sys_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	char				mbr[0x89];
	char				err_info[0x135];
	part_info_sys_t		part_info[4];
	short				end_flag;
}mbr_sys_t;
#pragma pack(pop)


#endif	/* __BOOT_STANDBY_H_ */
