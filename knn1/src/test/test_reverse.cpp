#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	//float data[2][2] = {{0,255}, {255,0}};
	//Mat src = Mat(2, 2, CV_32F, data);
	//cout << src << endl;
#ifdef ONE
	for(int i = 0; i < src.cols; ++i){
		for(int j = 0; j < src.rows; ++j ){
			src.at<int>(i, j) = 255 - src.at<int>(i, j);
		}
	}
#endif
	Mat src = imread("./chepai2.jpg");

#ifdef TWO
	src = src<100;
#endif
	
	imwrite("./chepai3.jpg", src);

	//cout << src << endl;

	return 0;
}
