#include "bmpfunc.h"
#include "bmpheader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void BMP_color(BMP_Image*, int);
void BMP_zhuanhuan(BMP_Image*);
void BMP_newzhuanhuan(BMP_Image*);
void bianyvanjianc(BMP_Image*);
double jishuan(char, char, char);
void zhuanhuan(BMP_Image*);
int main()
{
	char a[20];
	char a1[30] = { "new" };
	printf("请输入需要转换的照片:");
	scanf("%s", a);
	BMP_Image* BMP_Ptr = BMP_open(a);
	if (BMP_Ptr == NULL)
	{
		printf("图像错误，请确保输入正确的BMP格式图片\n");
		system("pause");
		return 0;
	}
	printf("请输入要转换的格式:	\n	输入1使某个颜色翻转\n	输入2使颜色更白输入\n	3使提取边缘信息\n	输入4使所有颜色翻转");
	int n;
	scanf("%d", &n);
	int newu = 0;
	 switch (n)
	{
	 case 1:
		 int x;
		 printf("请输入要翻转的颜色：\n0代表蓝色\n1代表l绿色\n2代表红色\n");
		 do {
			 if (newu > 0)
			 {
				 printf("请重新输入\n");
			 }
			 scanf("%d", &x);
		 } while (x != 2 && x != 1 && x != 0);
		 BMP_color(BMP_Ptr, x);
		 return 0;
	 case 2:
		 BMP_newzhuanhuan(BMP_Ptr);
	 case 3:
		 bianyvanjianc(BMP_Ptr);
	 case 4:
		 BMP_newzhuanhuan(BMP_Ptr);
	}

	strcat(a1, a);
	BMP_save(BMP_Ptr, a1);
	BMP_destroy(BMP_Ptr);
	printf("已完成");
	return 0;
}
void BMP_color(BMP_Image* img, int color)
{
	
	int pxl=0;
	for ( pxl = color; pxl < (img->data_size); pxl++);
	{
		if (pxl % 3 != 0)
		{
			img->data[pxl] = 0;
		}
	}
	return;
}
void zhuanhuan(BMP_Image* img)
{
	int pxl = 0;
	for (pxl = 0; pxl < (img->data_size); pxl++)
	{
		img->data[pxl] = 255 - (img->data[pxl])/2;
	}
	return;
}
void BMP_zhuanhuan(BMP_Image* img)
{
	int pxl = 0;
	for (pxl = 0; pxl < (img->data_size); pxl = pxl+1)
	{
		img->data[pxl] = 255 - (img->data[pxl]);
	}
	return;
}
void bianyvanjianc(BMP_Image* img)
{
	int width = img->width;
	int height = img->height;
	char** twoDGray = (char**)malloc(sizeof(char*) * height);
	for (int i = 0; i < height; i++)
	{
		twoDGray[i] = (char*)malloc(sizeof(char) * width);
		if (twoDGray[i] == NULL)
		{
			return;
		}
	}
	int pxl = 0;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			twoDGray[row][col] = jishuan(img->data[pxl + 2], img->data[pxl + 1], img->data[pxl]);
			pxl = pxl + 3;
		}
	}
	//检测是否为边缘；
	int pxld = 0;
	for (int row = 0; row < height; row++)
	{
		pxld = pxld + 3;
		for (int col = 1; col < width - 1; col++)
		{
			int diff = twoDGray[row][col+1] - twoDGray[row][col - 1];
			if (diff > 160 || diff < -160)
			{
				img->data[pxld] = 255;
				img->data[pxld + 1] = 255;
				img->data[pxld + 2] = 255;
			}
			else
			{
				img->data[pxld] = 0;
				img->data[pxld + 1] = 0;
				img->data[pxld + 2] = 0;
			}
			pxld = pxld + 3;
		}
	}
	for (int row = 0; row < height; row++)
	{
		free(twoDGray[row]);
	}
	free(twoDGray);
	return;
}
double jishuan(char red, char green, char blue)
{
	double n = 0.2989 * (double)red + 0.5870 * green + 0.1140 * blue;
	return (int)n;
}
void BMP_newzhuanhuan(BMP_Image* img)
{
	for (int pxl = 0; pxl < img->data_size; pxl++)
	{
		img->data[pxl] = 255 - (img->data[pxl]);
	}
}
