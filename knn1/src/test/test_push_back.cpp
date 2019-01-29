#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	float data[1][2] = {11,11};
	Mat src = Mat(1, 2, CV_32F, data);

	float data1[1][2] = {77,77};
	Mat src1 = Mat(1, 2, CV_32F, data1);
	
	float data2[1][2] = {55,55};
	Mat src2 = Mat(1, 2, CV_32F, data2);
	
	float data3[1][2] = {33,33};
	Mat src3 = Mat(1, 2, CV_32F, data3);
	
	Mat ss;
	ss.push_back(src);
	ss.push_back(src1);
	ss.push_back(src2);
	ss.push_back(src3);

	cout << ss.cols  << endl;
	cout << ss.rows  << endl;
	
	Mat dd = ss.rowRange(0, 1);
	cout << dd << endl;
	
	Scalar mm = sum(dd);
	cout << mm.val[0] << endl;

	return  0;
}





























