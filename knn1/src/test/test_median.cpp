#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	float data[7][7] = {{1,1,1,1,1,1,1}, {1,1,1,0,1,1,1}, {1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}, 
						{1,1,1,1,1,1,1},{1,1,1,1,0,1,1},{1,1,1,1,1,1,1}};
	Mat src = Mat(7, 7, CV_32F, data);
	cout << src << endl;
	
	medianBlur(src, src, 3);	
	cout << src << endl;

	return 0;
}
