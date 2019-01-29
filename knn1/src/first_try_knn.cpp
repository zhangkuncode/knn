#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
 
#include <iostream>

using namespace std;

using namespace cv;
using namespace cv::ml;
 
int main(void){	
	float trainingData[24][2]={	{4, 3},{1, 3},{3, 3},{3, 7},
                                {3, 4},{4, 1},{1, 4},{5, 6},
                                {3, 7},{6, 2},{4, 6},{4, 4},
                                {5, 8},{7, 8},{7, 7},{10, 5},
                                {7, 6},{4, 10},{9, 7},{5, 4},
                                {8, 5},{6, 6},{7, 4},{8, 8}	};
	Mat train_data =  Mat(24, 2, CV_32FC1, trainingData);
	
	float responses[24] = {'B','B','B','B','B','B','B','B','B','B',
		             'G','G','G','G','G','G','G','G','G','G','G','G','G','G'};
	Mat train_label = Mat(24, 1, CV_32FC1, responses);
    
	int K = 3; 
	Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	knn->train(train_data, ROW_SAMPLE, train_label);	
	
	float test_data[2] = {4, 3};
	Mat test_dataMat = Mat(1, 2, CV_32FC1, test_data);
	Mat dist, response;
	float r = knn->findNearest(test_dataMat, K, noArray(), response, dist);
 
	cout<<"result:  "<< (char)r <<endl;
	cout << response << endl;
	cout << dist << endl;
	return 0;
}
