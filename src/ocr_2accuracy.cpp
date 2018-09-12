#include <iostream>
#include <ctime>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;

using namespace cv;
using namespace ml;

int samples = 300;
int classes = 10;
char file_path[255] = "../English/Fnt/Sample0";
char file_path2[225] = "img0";
char file_path3[225] = "-0";
static const int K = 23;
Mat train_data;
Mat train_classes;

void get_train_data();

int main(){	
    Ptr<KNearest> knn = KNearest::create();
	knn->setDefaultK(K);
	knn->setIsClassifier(true);
	
	get_train_data();
	
	train_data.convertTo(train_data, CV_32F);
	train_classes.convertTo(train_classes, CV_32F);
	
	knn->train(train_data, ROW_SAMPLE, train_classes);	

	int error = 0;
	char path[255] = "./my_led";
	char file[255];
	for(int i = 0; i < 10; ++i){
		sprintf(file, "%s/%d1.jpg", path, i);
		Mat src = imread(file, 0);
		src = src.reshape(0, 1);
		src.convertTo(src, CV_32F);
		Mat mytest;
		mytest.push_back(src);
		auto r = knn->findNearest(mytest, K, noArray());
		if(r != i){
			cout << i << " -> " << r  << endl;
			error++;
		}else{
			cout << i << " is ok" << endl;
		}
	}

	cout << "error: " << error << endl;
	
	return 0;
}

void get_train_data(){
	int i = 0, j = 0;
	char file[255];
	for(i = 1; i <= classes; ++i){
		for(j = 1; j <= samples; ++j){
			if(i < 10){
				if(j < 10){
					sprintf(file,"%s0%d/%s0%d%s000%d.png",
							file_path, i, file_path2, i, file_path3, j);
				} else if(j < 100) {
					sprintf(file,"%s0%d/%s0%d%s00%d.png",
							file_path, i, file_path2, i, file_path3, j);
				} else if(j < 1000){
					sprintf(file,"%s0%d/%s0%d%s0%d.png",
							file_path, i, file_path2, i, file_path3, j);
				} else {
					sprintf(file,"%s0%d/%s0%d%s%d.png",
							file_path, i, file_path2, i, file_path3, j);
				}
			} else {
				if(j < 10){
					sprintf(file,"%s10/%s%d%s000%d.png",
							file_path, file_path2, i, file_path3, j);
				} else if(j < 100) {
					sprintf(file,"%s10/%s%d%s00%d.png",
							file_path, file_path2, i, file_path3, j);
				} else if(j < 1000){
					sprintf(file,"%s10/%s%d%s0%d.png",
							file_path, file_path2, i, file_path3, j);
				} else {
					sprintf(file,"%s10/%s%d%s%d.png",
							file_path, file_path2, i, file_path3, j);
				}
			} 

			Mat src = imread(file, 0);		
			if(!src.data){
				perror("read data_image failed\n");
			}
			src = src.reshape(0, 1);
			src.convertTo(src, CV_32F);

			train_classes.push_back(i - 1); 
			train_data.push_back(src);
		}
	}
}
