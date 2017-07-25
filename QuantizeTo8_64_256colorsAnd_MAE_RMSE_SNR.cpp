#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
int main()
{
	double MAE(IplImage *Img1, IplImage *Img2);
	double RMSE(IplImage *Img1, IplImage *Img2);
	double SNR(IplImage *Img1, IplImage *Img2);
	char FileName[36] = "C:\\Users\\ray-c\\Desktop\\LENA.bmp";
	IplImage *Image1, *Image8, *Image64, *Image256;
	
	Image1 = cvLoadImage(FileName, CV_LOAD_IMAGE_GRAYSCALE);
	CvSize Size1 = cvGetSize(Image1);
	cvNamedWindow("Show Gray Image", 1);
	cvShowImage("Show Gray Image", Image1);
	
	Image8 = cvCreateImage(Size1, IPL_DEPTH_8U, 1);
	void QuantizeTo8colors(IplImage *Img1, IplImage *Img2);
	QuantizeTo8colors(Image1, Image8);
	cvNamedWindow("Show Gray_8 Image", 1);
	cvShowImage("Show Gray_8 Image", Image8);
	double a = cvNorm(Image1, Image8, CV_L1) / (Image1->width*Image1->height);
	cout << "cvNorm(Gray_8):" << a << endl;
	a = MAE(Image1, Image8);
	cout << "MAE(Gray_8):" << a << endl;
	a = RMSE(Image1, Image8);
	cout << "RMSE(Gray_8):" << a << endl;
	a = SNR(Image1, Image8);
	cout << "SNR(Gray_8):" << a << endl;
	
	Image64 = cvCreateImage(Size1, IPL_DEPTH_8U, 1);
	void QuantizeTo64colors(IplImage *Img1, IplImage *Img3);
	QuantizeTo64colors(Image1, Image64);
	cvNamedWindow("Show Gray_64 Image", 1);
	cvShowImage("Show Gray_64 Image", Image64);
	double b = cvNorm(Image1, Image64, CV_L1) / (Image1->width*Image1->height);
	cout << "cvNorm(Gray_64):" << b << endl;
	b = MAE(Image1, Image64);
	cout << "MAE(Gray_64):" << b << endl;
	b = RMSE(Image1, Image64);
	cout << "RMSE(Gray_64):" << b << endl;
	b = SNR(Image1, Image64);
	cout << "SNR(Gray_64):" << b << endl;
	
	Image256 = cvCreateImage(Size1, IPL_DEPTH_8U, 1);
	void QuantizeTo256colors(IplImage *Img1, IplImage *Img3);
	QuantizeTo256colors(Image1, Image256);
	cvNamedWindow("Show Gray_256 Image", 1);
	cvShowImage("Show Gray_256 Image", Image256);
	double c = cvNorm(Image1, Image256, CV_L1) / (Image1->width*Image1->height);
	cout << "cvNorm(Gray_256):" << c << endl;
	c = MAE(Image1, Image256);
	cout << "MAE(Gray_256):" << c << endl;
	c = RMSE(Image1, Image256);
	cout << "RMSE(Gray_256):" << c << endl;
	c = SNR(Image1, Image256);
	cout << "SNR(Gray_256):" << c << endl;
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
	pv[i] = i * 4;
	for (int y = 0; y<Img1->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		unsigned char* ptr3 = (unsigned char*)(Img3->imageData + y*Img3->widthStep);
		for (int x = 0; x<Img1->width; x++)
			ptr3[x] = pv[ptr1[x] / 4];
	}
}
void QuantizeTo256colors(IplImage *Img1, IplImage *Img3)
{
	unsigned char pv[256];
	for (int i = 0; i < 256; i++)
	pv[i] = i;
	for (int y = 0; y<Img1->height; y++)
	{
	unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
	unsigned char* ptr3 = (unsigned char*)(Img3->imageData + y*Img3->widthStep);
	for (int x = 0; x<Img1->width; x++)
		ptr3[x] = pv[ptr1[x]];
	}
}
double MAE(IplImage *Img1, IplImage *Img2)
{
	double dSum = 0,dOutput;
	for (int y = 0; y<Img1->height; y++)
	{
	unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
	unsigned char* ptr2 = (unsigned char*)(Img2->imageData + y*Img2->widthStep);
	for (int x = 0; x<Img1->width; x++)
		dSum += abs(ptr1[x] - ptr2[x]);
	}
	dOutput = dSum / (Img1->height*Img1->width);
	return dOutput;
}
double RMSE(IplImage *Img1, IplImage *Img2)
{
	double dSum = 0, dOutput;
	for (int y = 0; y<Img1->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		unsigned char* ptr2 = (unsigned char*)(Img2->imageData + y*Img2->widthStep);
		for (int x = 0; x<Img1->width; x++)
			dSum += pow(ptr2[x] - ptr1[x],2);
	}
	dOutput = sqrt(dSum / (Img1->height*Img1->width));
	return dOutput;
}
double SNR(IplImage *Img1, IplImage *Img2)
{
	double dSum = 0, dOutput;
	for (int y = 0; y<Img1->height; y++)
	{
	unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
	unsigned char* ptr2 = (unsigned char*)(Img2->imageData + y*Img2->widthStep);
	for (int x = 0; x<Img1->width; x++)
		dSum += pow(ptr1[x] - ptr2[x], 2);
	}
	double up;
	up = Img1->height * Img1->width * pow(255,2);
	dOutput = 10 * log10(up / dSum);
	return dOutput;
}
