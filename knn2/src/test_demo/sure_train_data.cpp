#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("./English/Fnt/Sample001/img001-00001.png", 0);
	
	if(!src.data){
		perror("read failed\n");
	}
	
	src = src.reshape(0, 1);
	src.convertTo(src, CV_32F);

	cout << src.cols << endl;
	cout << src.rows << endl;

	cout << src.type() << endl;

	//imshow("origin", src);
	//waitKey(0);
	return 0;
}
