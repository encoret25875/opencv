#include <opencv\cv.h>
#include <opencv\highgui.h>
using namespace cv;
int main()
{
	char FileName[40] = "..\\Images\\LenaNoise.jpg";
	IplImage *Image1, *Image2;
	IplImage *yImg, *crImg, *cbImg;
	Image1 = cvLoadImage(FileName, 1);
	Image2 = cvCreateImage(cvSize(Image1->width, Image1->height), IPL_DEPTH_8U, 3);
	cvShowImage("src", Image1);
	//1. RGB->YCrCb
	cvCvtColor(Image1, Image2, CV_BGR2YCrCb);
	//2. Split->4 Channel(y,0,0.0)
	yImg = cvCreateImage(cvGetSize(Image2), IPL_DEPTH_8U, 1);
	cvSplit(Image2, yImg, 0, 0, 0);
	//3. Y->smooth(Gaussian)
	cvSmooth(yImg, yImg,CV_GAUSSIAN);
	//4. (y, 0, 0, 0)->merge
	cvMerge(yImg, 0, 0, 0, Image2);
	//5. YCrCb->RGB
	cvCvtColor(Image2, Image2, CV_YCrCb2BGR);
	cvShowImage("雜訊去除後", Image2);
	cvWaitKey(0);
	return 0;
}
