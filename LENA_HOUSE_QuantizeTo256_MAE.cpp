#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
using namespace std;
// 宣告一個資料型態 Palette_COLOR_TYPE ,
// 其結構為 BMP 檔頭中, 有關 Palette 的部分
typedef struct {
	unsigned char BLUE;
	unsigned char GREEN;
	unsigned char RED;
} Palette_COLOR_TYPE;
const int nc = 256;
int main() {
	int k = 0;
	IplImage* image1 = cvLoadImage("C:\\Users\\ray-c\\Desktop\\LENA.bmp", 1);
	IplImage* image2 = cvCreateImage(cvSize(image1->width, image1->height),IPL_DEPTH_8U, 3);
	image2 = cvCloneImage(image1);
	Palette_COLOR_TYPE ColorSet[nc];
	Palette_COLOR_TYPE FindBestColor(unsigned char, unsigned char, unsigned char,Palette_COLOR_TYPE*);
	for (int r = nc - 1; r > 0; r -= 32)
	for (int g = nc - 1; g > 0; g -= 32)
	for (int b = nc - 1; b > 0; b -= 64) {
		ColorSet[k].RED = (unsigned char)r;
		ColorSet[k].GREEN = (unsigned char)g;
		ColorSet[k].BLUE = (unsigned char)b;
		//cout<<"k="<<k<<" " << (int)ColorSet[k].RED << " " <<
		(int)ColorSet[k].GREEN << " " << (int)ColorSet[k].BLUE << endl;
		++k;
	}
	//影像量化成256色影像
	for (int y = 0; y < image2->height; y++) {
		char* ptr1 = (char*)(image2->imageData + y*image2->widthStep);
		for (int x = 0; x < image2->width; x++) {
			Palette_COLOR_TYPE Color =
			FindBestColor(ptr1[3 * x], ptr1[3 * x + 1], ptr1[3 * x + 2],
			ColorSet);
			ptr1[3 * x] = Color.BLUE;
			ptr1[3 * x + 1] = Color.GREEN;
			ptr1[3 * x + 2] = Color.RED;
		}
	}
	cvNamedWindow("ShowLENA256Colors", 0);
	cvShowImage("ShowLENA256Colors", image2);
	cvNamedWindow("ShowLENA", 0);
	cvShowImage("ShowLENA", image1);
	cout << "MAE=" << cvNorm(image1, image2, CV_L1) / (image1->width*image1->height);
	waitKey(0);
}
Palette_COLOR_TYPE FindBestColor(unsigned char b, unsigned char g, unsigned char r,Palette_COLOR_TYPE* ColorSet)
{
	int k =255- ((r / 32) * 32 + (g / 32) * 4 + b / 64);
	Palette_COLOR_TYPE BestColor;
	BestColor.RED = ColorSet[k].RED;
	BestColor.GREEN = ColorSet[k].GREEN;
	BestColor.BLUE = ColorSet[k].BLUE;
	return BestColor;
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
