#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("./chepai2.jpg", 0);
	
	//cout << src.cols << endl;
	//cout << src.rows << endl;

	//imshow("origin", src);
	threshold(src, src, 100, 255, THRESH_BINARY);

/*	for(int i = 0; i < src.cols; ++i){
		for(int j = 0; j < src.rows; ++j ){
			src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);
		}
	}
*/
	src = src < 100;
	imwrite("./chepai3.png", src);
//	imshow("reverse", src);
	
//  GaussianBlur(src, src, Size( 5, 5 ), 0, 0 );	
//	imshow("gaussian", src);	
//	waitKey(0);
//	cout << src << endl;

	return 0;
}
