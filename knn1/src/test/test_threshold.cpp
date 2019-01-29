#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	float data[4][2] = {{1,1}, {33,33}, {55,55}, {77,77}};
	Mat src = Mat(4, 2, CV_32F, data);
	cout << src << endl;
	
	threshold(src, src, 44, 255, THRESH_BINARY);

	cout << src << endl;

	return 0;
}
