#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("../../data/0/000.pbm", 0);
	Mat src2 = imread("../../data/0/000.pbm", 0);
	
	src = src.reshape(0, 1);
	src2 = src2.reshape(0, 1);

	Mat sss;
	sss.push_back(src);
	sss.push_back(src2);
	
	cout << "size: " << sss.size() << endl;
	
	int dis = 0;
	for(int i = 0; i < src.cols; ++i){
		dis += (src.at<uchar>(0, i) - src2.at<uchar>(0, i)) * 
			  (src.at<uchar>(0, i) - src2.at<uchar>(0, i));
	}
	cout << dis << endl;
	
	int dis2;
	for(int i = 0; i < src.cols; ++i){
		dis += (sss[0].at<uchar>(0, i) - sss[1].at<uchar>(0, i)) * 
			  (sss[0].at<uchar>(0, i) - sss[1].at<uchar>(0, i));
	}
	cout << dis2 << endl;
	
	return 0;
}
