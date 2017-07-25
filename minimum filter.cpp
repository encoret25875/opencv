#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
#include <algorithm>
using namespace std;
using namespace cv;
using namespace std;
int main()
{
	char FileName[40] = "..\\Images\\HOUSE_Gray_Noise_1.bmp";
	IplImage *Image1, *Image2, *Image3;
	Image1 = cvLoadImage(FileName, 0);
	Image2 = cvCreateImage(cvSize(Image1->width, Image1->height),
	IPL_DEPTH_8U, 1);
	Image3 = cvCreateImage(cvSize(Image1->width, Image1->height),
	IPL_DEPTH_8U, 1);
	void MinFilter(IplImage*, IplImage*, int, int);
	MinFilter(Image1, Image2, Image1->width, Image1->height);
	cvSub(Image1, Image2, Image3);
	cvShowImage("Tested Image", Image1);
	cvShowImage("Min Result", Image2);
	cvShowImage("O-M Result", Image3);
	cvWaitKey(0);
}
void MinFilter(IplImage*src, IplImage*dst, int w, int h)
{
	//unsigned char garray[w][h];
	unsigned char **garray;
	garray = new unsigned char * [w];
	for (int i = 0; i<w; i++)
		garray[i] = new unsigned char[h];
	for (int y = 0; y<src->height; y++) // 抓取 image data到garray二維陣列
	{
		unsigned char* ptr1 = (unsigned char*)(src->imageData + y*src->widthStep);
		for (int x = 0; x<src->width; x++)
			garray[x][y] = (unsigned char)ptr1[x];
	}
	unsigned char t[9];
	for (int i = 1; i<h - 1; i++)
	{
		unsigned char* ptr2 = (unsigned char*)(dst->imageData + i*dst->widthStep);
		for (int j = 1; j<w - 1; j++)
		{
			//從garray二維陣列抓取3 3子陣列，以便排序
			for (int k = 0; k < 9; k++)
				t[k] = garray[j + (k / 3) - 1][i + k % 3 - 1];
			sort(t,t+9); //排序
			//將最小值放回指定之j,i處
			ptr2[j] = (unsigned char)t[0];
		}
	}
} 
