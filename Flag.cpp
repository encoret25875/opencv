#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
using namespace std;
typedef struct {
	unsigned char BLUE;
	unsigned char GREEN;
	unsigned char RED;
} Palette_COLOR_TYPE;
const int width = 256, height = 160;
int main() {
	void make_ColorSet(void);
	void plot_Palette(IplImage*);
	
	IplImage* image1 = cvCreateImage(cvSize(width, height), 8, 3);
	cvNamedWindow("�k��", 1);
	cvRectangle(image1, cvPoint(0,0) , cvPoint(85, 160) ,CV_RGB(0, 35,149) , CV_FILLED);
	cvRectangle(image1, cvPoint(85, 0) , cvPoint(170, 160), CV_RGB(255, 255, 255),CV_FILLED);
	cvRectangle(image1, cvPoint(170, 0), cvPoint(256, 160), CV_RGB(237, 41, 57) ,CV_FILLED);
	cvShowImage("�k��", image1);
	cvSaveImage("�k��.bmp", image1);
	
	IplImage* image2 = cvCreateImage(cvSize(width, height), 8, 3);
	cvNamedWindow("����", 1);
	cvRectangle(image2, cvPoint(0, 0) , cvPoint(256, 53) , CV_RGB(174, 28, 40) ,CV_FILLED);
	cvRectangle(image2, cvPoint(0, 53) , cvPoint(256, 106), CV_RGB(255, 255, 255),CV_FILLED);
	cvRectangle(image2, cvPoint(0, 106), cvPoint(256, 160), CV_RGB(33, 70, 139) ,CV_FILLED);
	cvShowImage("����", image2);
	cvSaveImage("����.bmp", image2);
	
	IplImage* image3 = cvCreateImage(cvSize(width, height), 8, 3);
	cvNamedWindow("�饻", 1);
	cvSet(image3, cvScalar(255, 255, 255));
	cvCircle(image3, cvPoint(width / 2, height / 2), height / 4, cvScalar(0, 0, 255),CV_FILLED, 8);
	cvShowImage("�饻", image3);
	cvSaveImage("�饻.bmp", image3);
	
	cvWaitKey(0);
	
	cvReleaseImage(&image1);
	cvDestroyWindow("�k��");
	cvReleaseImage(&image2);
	cvDestroyWindow("����");
	cvReleaseImage(&image3);
	cvDestroyWindow("�饻");
	return 0;
}
