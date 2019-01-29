#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;

using namespace cv;
using namespace ml;

/*---------------------init data-------------------------*/
int samples = 50;
int classes = 10;
char file_path[255] = "../data";
int width = 40;
int height = 50;
static const int K = 3;
Mat train_data;
Mat train_classes;
Mat test_data;

/*-----set train_data, train_classes, test_data---------*/
void get_train_data();
void set_test_data(const char* c);

void preprocess(Mat &src, int new_width, int new_height);

int main(){	
	double time_cost = static_cast<double>(getTickCount()); 	
/*--------------------KNN init---------------------------*/
    Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	
	get_train_data();

/*-------------train() argument must is CV_32F-----------*/
	train_data.convertTo(train_data, CV_32F);
	train_classes.convertTo(train_classes, CV_32F);

/*------------------------train--------------------------*/
	knn->train(train_data, ROW_SAMPLE, train_classes);	

//	set_test_data("../data/8/890.pbm");
/*-----because of train_data if handwrite, ocr failed----*/
	test_data = imread("./chepai2.jpg", 0);
	threshold(test_data, test_data, 100, 255, THRESH_BINARY);
	test_data = test_data < 100;
	test_data.convertTo(test_data, CV_32F);
	test_data = test_data.reshape(0, 1);
	
/*----------------find nearest neighbour------------------*/
	Mat neighbour, distance;

	cout << "train data" << endl;
	cout << train_data.rows << endl;
	cout << train_data.cols << endl;
	cout << train_data.type()  << endl;

	cout << "test data" << endl;
	cout << test_data.rows << endl;
	cout << test_data.cols << endl;
	cout << test_data.type()  << endl;

	auto r = knn->findNearest(test_data, K, noArray(), neighbour, distance);

/*-----------------------show-----------------------------*/
	cout<<"result: "<< r <<endl;
	/*cout << "neighbour: " << neighbour << endl;
	cout << "distance: " << distance << endl;

	time_cost = ((double)getTickCount() - time_cost) / getTickFrequency(); 	
	cout << "cost time: " << time_cost << endl;
	*/
	return 0;
}

void get_train_data(){
	int i = 0, j = 0;
	char file[255];
	for(i = 0; i < classes; ++i){
		for(j = 0; j < samples; ++j){
			if(j<10){
				sprintf(file,"%s/%d/%d0%d.pbm",file_path, i, i, j);
			} else {
				sprintf(file,"%s/%d/%d%d.pbm",file_path, i, i, j);
			}
			Mat src = imread(file, 0);		
			if(!src.data){
				perror("read data_image failed\n");
			}

			preprocess(src, width, height);

			//set train_classes
			train_classes.push_back(i); 

			//set train_data
			src = src.reshape(0,1);
			train_data.push_back(src);
		}
	}
}

void set_test_data(const char* c){
	Mat temp = imread(c, 0);
	if(!temp.data){
		perror("read test_image failed\n");
	}
		
	preprocess(temp, width, height);
	
	temp = temp.reshape(0, 1);

	test_data.push_back(temp);	
/*----------findNearest() argument must is CV_32F---------*/
	test_data.convertTo(test_data, CV_32F);
}

void preprocess(Mat &src, int new_width, int new_height){
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
		data = src.rowRange(i, i + 1);
		Scalar sss = sum(data);
		if(sss.val[0] < max.val[0]){
			y_min = i;
			break;
		}
	}
	
	src = src(Rect(x_min, y_min, new_width, new_height));
	src = src.clone();
}
