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
const int nc = 216;
const int width = 720, height = 120, cellw = 20, cellh = 20;
const int ch = height / cellh, cw = width / cellw;
Palette_COLOR_TYPE ColorSet[ch][cw];
int main() {
	void make_ColorSet(void);
	void plot_Palette(IplImage*);
	IplImage* image = cvCreateImage(cvSize(width, height), 8, 3);
	cvNamedWindow("Show216Colors", 1);
	cvSet(image, cvScalar(255, 255, 255));
	make_ColorSet();
	plot_Palette(image);
	cvShowImage("Show216Colors", image);
	cvSaveImage("216Colors.bmp", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyWindow("Show216Colors");
	return 0;
}
void make_ColorSet(void) {
	int k = 0;
	int p[6] = {0,33,66,99,204,255};
	for (int r = 0; r<6; r++)
		for (int g = 0; g<6; g++)
			for (int b = 0; b < 6; b++)
			{ 
			ColorSet[k / cw][k%cw].RED = (unsigned char)p[r];
			ColorSet[k / cw][k%cw].GREEN = (unsigned char)p[g];
			ColorSet[k / cw][k%cw].BLUE = (unsigned char)p[b];
			++k;
			}
}
void plot_Palette(IplImage* img) {
	CvPoint pt1, pt2;
	for (int y = 0; y<img->height; y += cellh)
	{
		pt1.y = y; pt2.y = cellh + y;
		for (int x = 0; x<img->width; x += cellw)
		{
			pt1.x = x; pt2.x = cellw + x;
			cvRectangle(img, pt1, pt2, cvScalar(128, 128, 128));
			cvFloodFill(img,
						cvPoint(pt1.x + 1, pt1.y + 1),
						cvScalar(ColorSet[y / cellh][x / cellw].BLUE,
						ColorSet[y / cellh][x / cellw].GREEN,
						ColorSet[y / cellh][x / cellw].RED)
					   );
		}
	}
}
