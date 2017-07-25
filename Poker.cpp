#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <string>
using namespace std;
using namespace cv;
const int np = 52;
string s[np] = { "01","02","03","04","05","06","07","08","09","10","11","12","13",
				 "14","15","16","17","18","19","20","21","22","23","24","25","26",
				 "27","28","29","30","31","32","33","34","35","36","37","38","39",
				 "40","41","42","43","44","45","46","47","48","49","50","51","52" 
			   };
int main()
{
	string filename[np];
	cout << "Please using your hand touch on your heart !\n";
	cout << "Selecting a poker in your mind and answer the following question.\n";
	void initializeFilePathName(string *fn);
	int processPoker(string *fn);
	void displayPoker(int sp, int k, string *fn);
	initializeFilePathName(filename);
	int num = processPoker(filename);
	cout << "\nCan you believe!!! The magic thing will be happen !!\nThe poker in your mind is ..."<<endl;
	cvDestroyAllWindows();
	displayPoker(num, 0, filename);
	cvWaitKey(0);
	return 0;
}
void initializeFilePathName(string *fn)
{
	for (int i = 0; i<np; i++)
		fn[i] = "C:\\poker\\";
	for (int i = 0; i<np; i++)
		fn[i] = fn[i] + s[i] + ".JPG";
}
void displayPoker(int sp, int k, string *fn)
{
	string ch;
	Mat image[np];
	ch = fn[sp];
	namedWindow(ch, 0);
	resizeWindow(ch, 150, 180);
	moveWindow(ch, k % 13 * 75, k / 13 * 150 + 300);
	image[k] = imread(ch, 1);
	imshow(ch, image[k]);
	waitKey(1);
}
int processPoker(string *fn)
{
	int ans = 0;
	char input;
	for (int i = 1; i < 64; i*=2)
	{
		int iMove=0;
		for (int j = 0; j < 52; j++)
			if (j & i)
				displayPoker(j, iMove++, fn);
		cout << "裡面有嗎(y/n)?\n";
		cin >> input;
		if (input == 'y')
			ans += i;
		cvDestroyAllWindows();
	}
	if (ans > 51)
		ans = 51;
	return ans;
}
