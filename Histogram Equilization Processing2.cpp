#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
const int gl = 256;
int main()
{
	IplImage * image = cvLoadImage("..\\Images\\DarkLENA .bmp");
	//顯示原圖
	cvShowImage("Source", image);
	cvSaveImage("Source.jpg", image);
	IplImage* eqlimage = cvCreateImage(cvGetSize(image), image->depth, 3);
	//分別均衡化每個信道
	IplImage* redImage = cvCreateImage(cvGetSize(image), image->depth, 1);
	IplImage* greenImage = cvCreateImage(cvGetSize(image), image->depth, 1);
	IplImage* blueImage = cvCreateImage(cvGetSize(image), image->depth, 1);
	cvSplit(image, blueImage, greenImage, redImage, NULL);
	cvEqualizeHist(redImage, redImage);
	cvEqualizeHist(greenImage, greenImage);
	cvEqualizeHist(blueImage, blueImage);
	//均衡化後的圖像
	cvMerge(blueImage, greenImage, redImage, NULL, eqlimage);
	cvShowImage("Equalized", eqlimage);
	cvWaitKey(0);
}
void DrawPDFGraph(IplImage *Img1, IplImage *Img2)
{
	double pdf[gl] = { 0.0 };
	int hist[gl] = { 0 };
	Img2->origin = 1;
	for (int y = 0; y<Img1->height; y++)
	{ 
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		for (int x = 0; x<Img1->width; x++)
			hist[ptr1[x]]++;
	}
	for (int x = 0; x<gl; x++)
		pdf[x] = hist[x] *1.0 / (Img1->width*Img1->height);
	for (int x = 1; x<gl; x++)
		pdf[x] += pdf[x - 1];
	cvZero(Img2);
	for (int x = 1; x<gl; x++)
		cvLine(Img2,cvPoint(x - 1, cvRound(pdf[x-1] * 255)),cvPoint(x, cvRound(pdf[x] * 255)),cvScalar(255),1,8);
}
void DrawHistogram(IplImage *Img1, IplImage *Img2)
{
	int hist[gl] = { 0 };
	Img2->origin = 1;
	for (int y = 0; y<Img1->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(Img1->imageData + y*Img1->widthStep);
		for (int x = 0; x<Img1->width; x++)
			hist[ptr1[x]]++;
	}
	cvZero(Img2);
	for (int x = 0; x<gl; x++)
		cvLine(Img2,cvPoint(x, hist[x] / 10), cvPoint(x, 0), cvScalar(128),1,8);
}
