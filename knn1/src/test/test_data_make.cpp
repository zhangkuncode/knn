#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("./chepai2.jpg", 0);
	cout << "src type: " << src.type() << endl;
//	imshow("chepai2", src);
	threshold(src, src, 100, 255, THRESH_BINARY);
	src = src < 100;
	src.convertTo(src, CV_32F);
	cout << "src1 type: " << src.type()  << endl;
	
//	imshow("chepai3", src);

	Mat src2 = imread("./cehpai3.jpg");
	//cout << "src2 type: " << src2.type()  << endl;
	
//	imshow("chepai33", src2);

//	waitKey(0);
	return 0;
}

