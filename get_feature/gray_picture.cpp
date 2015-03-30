#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int number_picture=100000;
	int size_picture=96*96*3;
	int size_gray_picture=96*96;

	char *buffer=new char[size_picture];
	int *b=new int[size_picture];
	float *c=new float[size_gray_picture];
	ifstream fp("../data/stl10/unlabeled_X.bin",ios::in|ios::binary);
	ofstream fp1("../data/stl10/gray_unlabeled_X.bin",ios::out|ios::binary|ios::app);
	
	for(int i=0;i<number_picture;i++){
		fp.read(buffer,size_picture);
		unsigned char a=0;
		for(int j=0;j<size_picture;j++){
			a=buffer[j];
			b[j]=a;
		}

		for(int j=0;j<size_gray_picture;j++){
			c[j]=(b[j]*30+b[j+96*96]*59+b[j+2*96*96]*11+50)/100.0;
		}
		fp1.write((char*)c,sizeof(float)*size_gray_picture);
	}
	delete[] buffer;
	delete[] b;
	fp.close();
	fp1.close();
	return 0;
}

