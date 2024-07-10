//  bmpheader.h
#ifndef _BMPHEADER_H_
#define _BMPHEADER_H_
#include <stdint.h>
//  告诉编译器在属性间不要加空格,确保一个BMP文件的头文件只有54个字节
#pragma pack(1)
typedef struct
{
	uint16_t type;
	uint32_t size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
	uint32_t header_size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bits;
	uint32_t compression;
	uint32_t imagesize;
	uint32_t xresolution;
	uint32_t yresolution;
	uint32_t ncolours;
	uint32_t importantcolours;
}BMP_Header;
#endif

