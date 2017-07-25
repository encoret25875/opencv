#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
using namespace std;
const int gl = 256;
int main()
{
	IplImage * image = cvLoadImage("..\\Images\\MONKEY.bmp");
	//顯示原圖
	cvShowImage("Source", image);
	cvSaveImage("Source.jpg", image);
	IplImage * redHist, *greenHist, *blueHist;
	redHist = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 3);
	greenHist = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 3);
	blueHist = cvCreateImage(cvSize(gl, gl), IPL_DEPTH_8U, 3);
	//分開每個信道
	void DrawSplitHistogram(IplImage *image, IplImage * Hist1, IplImage *Hist2,IplImage *Hist3);
	DrawSplitHistogram(image, redHist, greenHist, blueHist);
	cvShowImage("redHist", redHist);
	cvShowImage("greenHist", greenHist);
	cvShowImage("blueHist", blueHist);
	cvWaitKey(0);
}
void DrawSplitHistogram(IplImage *image, IplImage * redHist, IplImage *greenHist,IplImage *blueHist)
{
	int hist[3][gl] = { 0 };
	redHist->origin = 1; greenHist->origin = 1; blueHist->origin = 1;
	for (int y = 0; y<image->height; y++)
	{
		unsigned char* ptr1 = (unsigned char*)(image->imageData + y*image->widthStep);
		for (int x = 0; x < image->width; x++)
			for (int z = 0; z < 3; z++)
				hist[z][ptr1[3*x + z]]++;
	}
	cvZero(redHist); cvZero(greenHist); cvZero(blueHist);
	for (int x = 0; x<gl; x++)
		cvLine(blueHist,cvPoint(x, hist[0][x] / 10), cvPoint(x, 0), CV_RGB(0,0,255),1, 8);
	for (int x = 0; x<gl; x++)
		cvLine(greenHist,cvPoint(x, hist[1][x] / 10), cvPoint(x, 0), CV_RGB(0, 255,0),1,8);
	for (int x = 0; x<gl; x++)
		cvLine(redHist,cvPoint(x, hist[2][x] / 10), cvPoint(x, 0), CV_RGB(255, 0,0),1,8);
} 

