#define _CRT_SECURE_NO_WARNINGS
#ifndef _BMPIMAGE_H
#define _BMPIMAGE_H

#include "bmpheader.h"

typedef struct {
    BMP_Header header;
    unsigned int data_size;
    unsigned int width;
    unsigned int height;
    unsigned int bytes_per_pixel;
    unsigned char* data;
} BMP_Image;

#endif




#include <stdio.h>
#include <stdlib.h>
//#include "bmpfile.h"
/* ��BMP�ļ� */
BMP_Image* BMP_open(const char* filename);

/* ��BMP�ļ�����Ϊָ�������� */
int BMP_save(BMP_Image image, const char* filename);

/* �ͷ�BMP�ڴ� */
void BMP_destroy(BMP_Image* image);

#define MAGTC_VALUE 0x4D42
#define BITS_PER_PIXEL 24
#define NUM_PLANE 1
#define COMPRESSION 0
#define BITS_PER_BYTE 8
//�ж��Ƿ�Ϊ��Ч��Ч����1����Ч����0��
static int checkHeader(BMP_Header* hdr) {
    if (hdr->type != MAGTC_VALUE) {
        return 0;
    }
    if (hdr->bits != BITS_PER_PIXEL && hdr->bits != 32) {
        return 0;
    }
    if (hdr->planes != NUM_PLANE) {
        return 0;
    }
    if (hdr->compression != COMPRESSION) {
        //return 0;
    }
    return 1;
}

BMP_Image* cleanUp(FILE* fptr, BMP_Image* img){
    if (fptr != NULL) {
        fclose(fptr);
    }
    if (img != NULL) {
        if (img->data != NULL) {
            free(img->data);
        }
        free(img);
    }
    return NULL;
}
BMP_Image* BMP_open(const char* filename) {
    FILE* fptr;
    BMP_Image* img = NULL;
    fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        return cleanUp(fptr, img);
    }
    img = (BMP_Image*)malloc(sizeof(BMP_Image));
    if (fread(&(img->header), sizeof(BMP_Header), 1, fptr) != 1) {
        return cleanUp(fptr, img);
    }
    if (checkHeader(&(img->header)) == 0) {
        return cleanUp(fptr, img);
   }
    img->data_size = (img->header).size - sizeof(BMP_Header);
    img->width = (img->header).width;
    img->height = (img->header).height;
    img->bytes_per_pixel = (img->header).bits / BITS_PER_BYTE;
    img->data = (unsigned char*)malloc(sizeof(unsigned char) * (img->data_size));
    if (img->data == NULL) {
        return cleanUp(fptr, img);
    }
    fread(img->data, sizeof(char), img->data_size, fptr);
    char onebyte;
    if (fread(&onebyte, sizeof(char), 1, fptr) != 0) {
        return cleanUp(fptr, img);
    }
    fclose(fptr);
    return img;
}
int BMP_save(const BMP_Image* img, const char* filename) {
        FILE* fptr;
    fptr = fopen(filename, "wb");
    if (fptr == NULL) {
        return 0;
    }
    if (fwrite(&(img->header), sizeof(BMP_Header), 1, fptr) != 1) {
        fclose(fptr);
        return 0;
    }
    fwrite(img->data, sizeof(char), img->data_size, fptr);
    fclose(fptr);
    return 1;
}
void BMP_destroy(BMP_Image* img) {
    free(img->data);
    free(img);
}