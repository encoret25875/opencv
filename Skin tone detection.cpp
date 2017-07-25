#include <opencv/highgui.h>
#include <opencv/cv.h>
int main()
{
	IplImage * img = cvLoadImage("..\\Images\\DesignProduct.jpg", 1);
	cvNamedWindow("Sample Image");
	cvShowImage("Sample Image", img);
	cvNamedWindow("RGB Image");
	cvNamedWindow("YCrCb Image");
	IplImage * grey = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvInRangeS(img, cvScalar(0.279, 0.280 * 255, 0.36), cvScalar(0.291, 0.363, 0.465),grey);
	cvShowImage("RGB Image", grey);
	cvCvtColor(img, img, CV_BGR2YCrCb);
	cvInRangeS(img, cvScalar(0, 137, 77), cvScalar(256, 173, 128), grey);
	cvShowImage("YCrCb Image", grey);
	cvWaitKey(0);
	return 0;
}
