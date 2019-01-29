#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("../data/8/888.pbm", 0);
	cout << src.cols << endl;
	cout << src.rows << endl;
	imshow("origin", src);
	int x_min = 0, y_min = 0;
	int i = 0;
	Scalar max = Scalar(src.cols * 255);
	Mat data;
	// find x_min
	for(i = 0; i < src.cols; ++i){
		data = src.colRange(i, i + 1);
		Scalar sss = sum(data);
		if(sss.val[0] < max.val[0]){
			x_min = i;
			break;
		}
	}
	
	// find y_min
	max = Scalar(src.rows * 255);
	for(i = 0; i < src.rows; ++i){
		data = src.colRange(i, i + 1);
		Scalar sss = sum(data);
		if(sss.val[0] < max.val[0]){
			y_min = i;
			break;
		}
	}
	
	src = src(Rect(x_min, y_min, 40, 50));
	
	src = src.clone();

	cout << src.isContinuous() << endl;
	imshow("done", src);
	waitKey(0);
	return 0;
}






