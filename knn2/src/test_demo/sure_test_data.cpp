#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat test_data = imread("./chepai2.jpg", 0);
	threshold(test_data, test_data, 100, 255, THRESH_BINARY);
	test_data = test_data < 100;
	resize(test_data, test_data,Size(128, 128), 0, 0, INTER_LINEAR);
	
	cout << test_data.cols << endl;
	cout << test_data.rows << endl;

	imshow("done", test_data);
	waitKey(0);
	return 0;
}
