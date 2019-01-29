#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat test_data;
struct KNN{
	vector<Mat> train_data;
	vector<int> train_class;
	vector<int> distance;
};
int classes = 10;
int samples = 50;
int width = 50;
int height = 50;
char file_path[255] = "../data";
int K = 3;

void preprocess(Mat &src, int new_width, int new_height);
int find_knn(KNN const &knn, int K);

int main(){
	KNN knn;
	char file[255];
	for(int i = 0; i < classes; ++i){
		for(int j = 0; j < samples; ++j){
			if(j<10){
				sprintf(file,"%s/%d/%d0%d.pbm",file_path, i, i, j);
			} else {
				sprintf(file,"%s/%d/%d%d.pbm",file_path, i, i, j);
			}
			Mat temp = imread(file, 0);		
			if(!temp.data){
				perror("read data_image failed\n");
			}
			
			//preprocess(temp, width, height);
			knn.train_class.push_back(i); 
			temp = temp.reshape(0,1);
			knn.train_data.push_back(temp);
		}
	}
	
	test_data = imread("../data/9/999.pbm", 0);
	//preprocess(test_data, width, height);
	test_data = test_data.reshape(0, 1);

	for(int i = 0; i < knn.train_data.size(); ++i){
		int dis = 0;
		for(int j = 0; j < knn.train_data[0].cols; ++j){
			dis += (knn.train_data[i].at<uchar>(0, j) - test_data.at<uchar>(0, j)) *
				   (knn.train_data[i].at<uchar>(0, j) - test_data.at<uchar>(0, j));
		}
		knn.distance.push_back(dis);
	}
	
	cout << "result: " << find_knn(knn, K) << endl;

	return 0;
}

int find_max_num(int num[]){
	int max = num[0], max_num = 0;
	for(int i = 0; i < 10; ++i){
		if(max < num[i]){
			max = num[i];
			max_num = i;
		}
	}
	
	max = 0;
	
	return max_num;
}

int find_knn(KNN const &knn, int K){
	KNN temp = knn;
	for (int i = 1; i < temp.train_data.size(); ++i) {
		int j = i - 1;
		int x = temp.distance[i];
		Mat xx = temp.train_data[i];
		int xxx = temp.train_class[i];

		while (j >= 0 && (temp.distance[j] > x)) {
			temp.distance[j + 1] = temp.distance[j];
			temp.train_data[j + 1] = temp.train_data[j];
			temp.train_class[j + 1] = temp.train_class[j];
			
			j--;
		}
		
		temp.distance[j + 1] = x;
		temp.train_data[j + 1] = xx;
		temp.train_class[j + 1] = xxx;
	}
	
	int number[10] = {0};
	for(int i = 0; i < K; ++i){
		switch (temp.train_class[i]) {
			case 0 : number[0]++; break;
			case 1 : number[1]++; break;
			case 2 : number[2]++; break;
			case 3 : number[3]++; break;
			case 4 : number[4]++; break;
			case 5 : number[5]++; break;
			case 6 : number[6]++; break;
			case 7 : number[7]++; break;
			case 8 : number[8]++; break;
			case 9 : number[9]++; break;
		}
	}
	
	int kk[K];
	for(int i = 0; i < K; ++i){
		kk[i] = find_max_num(number);
	}

	int maxx = 0;
	for(int i = 0; i < K; ++i){
		if(maxx < kk[i]){
			maxx = kk[i];
		}
	}

	return maxx;
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
