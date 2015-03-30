#include"image.h"
#include<iostream>
using namespace std;

int main(){
	string inputfile="l2_hx_4.bin";
	string outpath="minist2_feature_h5/0_";
	int picture_row=12;
	int picture_col=12;

	int input_channel=1;
	int input_row=28;
	int input_col=28;
	int hidden_channel=3;

	int size=picture_row*picture_col*hidden_channel*input_row*input_col;
	float* Weight=new float[size];
	ifstream fp(inputfile.c_str(),ios::in|ios::binary);
	fp.read((char*)Weight,sizeof(float)*size);

	storeImage_onemap1(Weight,input_channel,input_row,input_col,picture_row,picture_col,hidden_channel,outpath);
	fp.close();
	delete[] Weight;
	return 0;
}
