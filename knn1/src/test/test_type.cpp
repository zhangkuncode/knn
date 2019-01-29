#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("./chepai3.jpg");
	
	imshow("origin", src);

	src.convertTo(src, CV_32F);	
	cout << src.type() << endl;
	
	waitKey(0);

	return 0;
}

