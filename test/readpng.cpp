#include <iostream>

using namespace std;
char file_path[255] = "./English/Fnt/Sample0";

void get_train_data();

int main(){	
	get_train_data();
	return 0;
}

void get_train_data(){
	int i = 0, j = 0;
	char file[255];
	char file_path2[225] = "img0";
	char file_path3[225] = "-0";
	int classes = 10;
	int samples = 1;

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
					sprintf(file,"%s10/%s0%d%s000%d.png",
							file_path, file_path2, i, file_path3, j);
				} else if(j < 100) {
					sprintf(file,"%s10/%s0%d%s00%d.png",
							file_path, file_path2, i, file_path3, j);
				} else if(j < 1000){
					sprintf(file,"%s10/%s0%d%s0%d.png",
							file_path, file_path2, i, file_path3, j);
				} else {
					sprintf(file,"%s10/%s0%d%s%d.png",
							file_path, file_path2, i, file_path3, j);
				}
			} 
			cout << file << endl;
		}
	}
}

