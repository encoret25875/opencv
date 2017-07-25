#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
using namespace std;
IplImage *image;
int main() {
	cvNamedWindow("Show image", 0);
	void onMouse(int event, int x, int y, int flags, void* param);
	cvSetMouseCallback("Show image", onMouse, NULL);
	image = cvLoadImage("..\\Images\\LENA.bmp", 1);
	cvShowImage("Show image", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyWindow("Show image");
}
void onMouse(int Event, int x, int y, int flags, void* param)
{
	static int cx, cy;
	if (Event == CV_EVENT_LBUTTONDOWN)
		cx = x; cy = y;
	if ((Event == CV_EVENT_LBUTTONUP) && (flags == 0))
	{
		cvDestroyWindow("Part Image");
		//�p����o����ϰ쪺�e��;
		int h = y - cy; int w = x - cx;
		//�]�w����ϰ쪺 ROI;
		cvSetImageROI(image, cvRect(cx, cy, w, h));
		//���ͻP����ϰ�P�j�p���l�v��;
		IplImage *sub_img = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
		cvZero(sub_img);
		//�]�w��i�l�v���� ROI;
		cvSetImageROI(sub_img, cvRect(0, 0, w, h));
		//��� ROI �ۥ[��l�v��;
		cvAddWeighted(image, 1.0, sub_img, 0.0, 0.0, sub_img);
		//�Ѱ� ROI;
		cvResetImageROI(image);
		//��ܤl�v��;
		cvNamedWindow("Part Image", 1);
		cvShowImage("Part Image", sub_img);
	}
}
