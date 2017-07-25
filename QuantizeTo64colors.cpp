#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
int main()
{
	char FileName[36] = "C:\\Users\\ray-c\\Desktop\\LENA.bmp";
	IplImage *Image1, *Image2, *Image3;
	Image1 = cvLoadImage(FileName, CV_LOAD_IMAGE_GRAYSCALE);
	CvSize Size1 = cvGetSize(Image1);
	cvNamedWindow("Show Gray Image", 1);
	cvShowImage("Show Gray Image", Image1);
	Image3 = cvCreateImage(Size1, IPL_DEPTH_8U, 1);
	void QuantizeTo64colors(IplImage *Img1, IplImage *Img3);
	QuantizeTo64colors(Image1, Image3);
	cvNamedWindow("Show Gray_64 Image", 1);
	cvShowImage("Show Gray_64 Image", Image3);
	double b = cvNorm(Image1, Image3, CV_L1) / (Image1->width*Image1->height);
	cout << "cvNorm(Gray_64):" << b << endl;
	waitKey(0);
	return 0;
}
void QuantizeTo8colors(IplImage *Img1, IplImage *Img2)
{
	unsigned char pv[8] = { 0,36,72,108,144,180,216,252 };
	for (int y = 0; y<Img1->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		unsigned char* ptr2 = (unsigned char*)(Img2->imageData + y*Img2->widthStep);
		for (int x = 0; x<Img1->width; x++)
			ptr2[x] = pv[ptr1[x] / 32];
	}
}
void QuantizeTo64colors(IplImage *Img1, IplImage *Img3)
{
	unsigned char pv[64];
	for (int i = 0; i < 64; i++)
		pv[i] = i*4;
	for (int y = 0; y<Img1->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		unsigned char* ptr3 = (unsigned char*)(Img3->imageData + y*Img3->widthStep);
		for(int x = 0; x<Img1->width; x++)
			ptr3[x] = pv[ptr1[x] / 4];
	}
}
