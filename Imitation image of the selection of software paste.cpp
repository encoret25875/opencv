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
		//計算獲得選取區域的寬高;
		int h = y - cy; int w = x - cx;
		//設定選取區域的 ROI;
		cvSetImageROI(image, cvRect(cx, cy, w, h));
		//產生與選取區域同大小的子影像;
		IplImage *sub_img = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
		cvZero(sub_img);
		//設定整張子影像維 ROI;
		cvSetImageROI(sub_img, cvRect(0, 0, w, h));
		//兩個 ROI 相加於子影像;
		cvAddWeighted(image, 1.0, sub_img, 0.0, 0.0, sub_img);
		//解除 ROI;
		cvResetImageROI(image);
		//顯示子影像;
		cvNamedWindow("Part Image", 1);
		cvShowImage("Part Image", sub_img);
	}
}
