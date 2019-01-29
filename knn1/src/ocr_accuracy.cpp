#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;

using namespace cv;
using namespace ml;

/*---------------------init data-------------------------*/
const int K = 3;
const int new_width = 50;
const int new_height = 70;
const int samples = 60;
const int classes = 10;
const char file_path[255] = "../data";
Mat train_data;
Mat train_classes;
Mat test_data;

/*-----set train_data, train_classes, test_data---------*/
void get_train_data();
void set_test_data(const char* c);

void preprocess(Mat &src, int new_width, int new_height);

void simple_check();

int main(){	
    Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	
	get_train_data();

	train_data.convertTo(train_data, CV_32F);
	train_classes.convertTo(train_classes, CV_32F);

	knn->train(train_data, ROW_SAMPLE, train_classes);	
	
	char file[255];
	int i = 0, j = 0;
	int error = 0;
	for(i = 0; i < 10; ++i){
		for(j = 50; j < 100; ++j){
			sprintf(file, "%s/%d/%d%d.pbm", file_path, i, i, j);
			Mat temp = imread(file, 0);
			if(!temp.data){
				perror("read file failed");				
			}
			preprocess(temp, new_width, new_height);
			temp = temp.reshape(0, 1);
			Mat mytest;
			mytest.push_back(temp);
			mytest.convertTo(mytest, CV_32F);
			auto r = knn->findNearest(mytest, K, noArray());
			if(r != i){
				error++;
			}
		}
	}
	
	cout << "accuracy: " << ( (float)(500-error) / 5 ) << "%" << endl;
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
			
			preprocess(src, new_width, new_height);
			
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

	preprocess(temp, new_width, new_height);
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
		data = src.colRange(i, i + 1);
		Scalar sss = sum(data);
		if(sss.val[0] < max.val[0]){
			y_min = i;
			break;
		}
	}
	
	src = src(Rect(x_min, y_min, new_width, new_height));
	src = src.clone();
}
