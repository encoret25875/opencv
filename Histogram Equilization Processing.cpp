#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
using namespace std;
const int gl = 256;
const int c = 50;
//灰階均衡化
int main()
{
	IplImage * src = cvLoadImage("..\\Images\\LENA.bmp",0);
	IplImage * srcHist, * srcPDF, *dstHist, *dstPDF;
	srcHist = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 1);
	srcPDF = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 1);
	dstHist = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 1);
	dstPDF = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 1);
	void DrawPDFGraph(IplImage* Img1, IplImage* Img2);
	void DrawHistogram(IplImage *Img1, IplImage *Img2);
	//DrawHistogram(Image1, Image2);
	//cvShowImage("Histogram", Image2);
	//顯示原圖
	cvNamedWindow("Source", 1);
	cvShowImage("Source", src);
	//show Histogra & PDF
	DrawHistogram(src, srcHist);
	cvShowImage("Source Histogram", srcHist);
	DrawPDFGraph(src, srcPDF);
	cvShowImage("Source PDF", srcPDF);
	cvEqualizeHist(src, src);
	//顯示Equalized圖
	cvNamedWindow("Equalized Image", 1);
	cvShowImage("Equalized Image", src);
	//show Histogra & PDF
	DrawHistogram(src, dstHist);
	cvShowImage("Equalized Histogram", dstHist);
	DrawPDFGraph(src, dstPDF);
	cvShowImage("Equalized PDF", dstPDF);
	waitKey(0);
	return 0;
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
