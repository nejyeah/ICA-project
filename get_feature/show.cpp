/*************************************************************************
    > File Name: show.cpp
    > Author: chenrudan
    > Mail: chenrudan123@gmail.com 
    > Created Time: 2014年08月27日 星期三 19时05分03秒
 ************************************************************************/

#include<iostream>
#include<fstream>
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

void show(string filename,string filename1,string filename2, int num, int channels, int size,int flag,string pngname);
void preprocess(float *,int);
void normalise(float *,int);

int main()
{

	//show("../data/stl10/test_cat.dat","test_R1.dat","test_R1.dat", 200, 3, 96, 0,"R1_t");
	//show("first_outcome_t.dat","second_R0_t.dat","second_Rn_t.dat", 200, 8, 78, 1,"R2_t");
	//show("first_outcome_600.dat","second_R0.dat","second_Rn.dat", 200, 8, 78, 1,"R2");
	//show("../data/stl10/gray_unlabeled_X.bin","first_R0_t1.dat","first_Rn_t1.dat", 200, 1, 96, 1,"l1_t1");
	//show("whiten_unlabeled_X.bin","first_R0_t4.dat","first_Rn_t4.dat", 200, 3, 96, 1,"l1_t4");
	//show("../data/MINIST/train-images.idx3-ubyte","minist1_R0_t4.dat","minist1_Rn_t4.dat", 800, 1, 28, 0,"minist1_t2");
	//show("minist1_outcome_t.dat","minist2_R0_t.dat","minist2_Rn_t.dat", 800, 3, 20, 1,"minist2_t2");
	
	//show h p lcn
	show("minist1_h_t1.dat","minist1_p_t1.dat","minist1_lc_t1.dat", 200, 3, 20, 1,"minist1_hplcn1/");
	//show("minist2_h_t4.dat","minist2_p_t4.dat","minist2_outcome_t4.dat", 200, 3, 12, 1,"minist2_hplcn4");
	//show("minist3_h_t1.dat","minist3_p_t1.dat","minist3_outcome_t1.dat", 800, 3, 4, 1,"minist3_hplcn1");
	//

	//show the activation feature
	//show("top1_h1_pixel.bin","l1_hx.bin","l1_hx1.bin",20*20*3, 1, 28, 1,"minist1_feature_h3/");
	//show("top1_p1_pixel.bin","l1_px.bin","l1_px1.bin",20*20*3, 1, 28, 1,"minist1_feature_p1/");
	//show("top1_p1_pixel.bin","l1_px2.bin","l1_px3.bin",20*20*3, 1, 28, 1,"minist1_feature_p2/");
	//
	//layer Reconstruct
	show("minist1_lc_t1.dat","minist2_R0_t2.dat","minist2_Rn_t2.dat", 200, 3, 20, 1,"minist2_R1/");
	show("minist1_lc_t1.dat","minist2_R0_t2_1.dat","minist2_Rn_t2_1.dat", 200, 3, 20, 1,"minist2_R2/");
	show("minist1_lc_t1.dat","minist2_R0_t2_2.dat","minist2_Rn_t2_2.dat", 200, 3, 20, 1,"minist2_R3/");
	show("minist1_lc_t1.dat","minist2_R0_t2_3.dat","minist2_Rn_t2_3.dat", 200, 3, 20, 1,"minist2_R4/");
	show("minist1_lc_t1.dat","minist2_R0_t2_4.dat","minist2_Rn_t2_4.dat", 200, 3, 20, 1,"minist2_R5/");
	
	//show("top2_h2_3_pixel.bin","l2_hx_3.bin","l2_hx1_3.bin",12*12*3, 1, 28, 1,"minist2_feature_h4/point/0_");
	//show("top2_h2_4_pixel.bin","l2_hx_4.bin","l2_hx1_4.bin",12*12*3, 1, 28, 1,"minist2_feature_h5/point/0_");
	//show("top2_p2_3_pixel.bin","l2_px_3.bin","l2_px1_3.bin",12*12*3, 1, 28, 1,"minist2_feature_p4/point/0_");
	//show("top2_p2_1_pixel.bin","l2_px2_1.bin","l2_px3_1.bin",12*12*3, 1, 28, 1,"minist2_feature_p2/point/1_");
	
	//get hplcn picture
	/*
	show("minist2_h_t2.dat","minist2_p_t2.dat","minist2_lc_t2.dat", 200, 3, 12, 1,"minist2_hplc1/");
	show("minist2_h_t2_1.dat","minist2_p_t2_1.dat","minist2_lc_t2_1.dat", 200, 3, 12, 1,"minist2_hplc2/");
	show("minist2_h_t2_2.dat","minist2_p_t2_2.dat","minist2_lc_t2_2.dat", 200, 3, 12, 1,"minist2_hplc3/");
	show("minist2_h_t2_3.dat","minist2_p_t2_3.dat","minist2_lc_t2_3.dat", 200, 3, 12, 1,"minist2_hplc4/");
	show("minist2_h_t2_4.dat","minist2_p_t2_4.dat","minist2_lc_t2_4.dat", 200, 3, 12, 1,"minist2_hplc5/");
	*/
	//show("top3_h2_pixel.bin","l3_hx.bin","l3_hx1.bin",4*4*3, 1, 28, 1,"minist3_feature_h1/");
	//show("top3_h2_pixel.bin","l3_hx2.bin","l3_hx3.bin",4*4*3, 1, 28, 1,"minist3_feature_h2/");
	//show("top3_p_pixel.bin","l3_px.bin","l3_px1.bin",4*4*3, 1, 28, 1,"minist3_feature_p1/");
	//show("top3_p_pixel.bin","l3_px2.bin","l3_px3.bin",4*4*3, 1, 28, 1,"minist3_feature_p2/");
	return 0;
}

void show(string filename, string filename1,string filename2,int num, int channels, int size, int flag,string pngname)
{
	ifstream fin(filename.c_str(), ios::binary);
	ifstream fin1(filename1.c_str(), ios::binary);
	ifstream fin2(filename2.c_str(), ios::binary);
	
	//minist
	//fin.seekg(16,ios::beg);
	//store picture
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	
	for(int i = 0; i < num; i++)
	{
		Mat dispImg;
		dispImg.create(Size((size + 1)*channels, (1 + size)*3), CV_8U);
		for(int j = 0; j < channels; j++)
		{
			Mat tmp(size, size, CV_8U);
			Mat tmp1(size, size, CV_8U);
			Mat tmp2(size, size, CV_8U);

			float *read_value = new float[size*size];
			float *read_value1 = new float[size*size];
			float *read_value2 = new float[size*size];
			
			if(flag==0){
				char *value=new char[size*size];
				fin.read(value,size*size);
				unsigned char a=0;
				for(int k=0;k<size*size;k++){
					a=value[k];
					read_value[k]=a/255.0;
				}
				delete[] value;
			}
			else{
				fin.read((char *)read_value,sizeof(float)*size*size);
			}
			fin1.read((char *)read_value1,sizeof(float)*size*size);
			fin2.read((char *)read_value2,sizeof(float)*size*size);
			
			normalise(read_value,size*size);
			normalise(read_value1,size*size);
			normalise(read_value2,size*size);

			for(int m = 0; m < size; m++)
			{
				for(int n = 0; n < size; n++)
				{
					tmp.at<uchar>(m,n) = read_value[m*size + n]*255.0;
					tmp1.at<uchar>(m,n) = read_value1[m*size + n]*255.0;
					tmp2.at<uchar>(m,n) = read_value2[m*size + n]*255.0;
				}
			}
			Mat imgROI = dispImg(Rect(j*(1+size), 0, size, size));  
			Mat imgROI1 = dispImg(Rect(j*(1+size), (1+size), size, size));  
			Mat imgROI2 = dispImg(Rect(j*(1+size), 2*(1+size), size, size));  
        	resize(tmp, imgROI, Size(size, size));
        	resize(tmp1, imgROI1, Size(size, size));
        	resize(tmp2, imgROI2, Size(size, size));

			delete[] read_value;
			delete[] read_value1;
			delete[] read_value2;
		}
		stringstream stream;
		stream<<i;
		string name="./"+pngname+"input_"+stream.str()+".png";
		//namedWindow(name, WINDOW_NORMAL);
		//imshow(name, dispImg);
		//store 
		imwrite(name,dispImg,compression_params);
		//waitKey();
		//destroyWindow(name);
	}
	fin.close();
	fin1.close();
	fin2.close();
}

void preprocess(float* read_value,int size){

	float mean=0.0;
	for(int j=0;j<size;j++){
		mean+=read_value[j];
	}
	mean=mean/size;
	for(int j=0;j<size;j++){
		read_value[j]=read_value[j]-mean;
	}
	
	float sum=0.0;
	for(int j=0;j<size;j++){
		sum+=read_value[j]*read_value[j];
	}
	sum=sqrt(sum);
	for(int j=0;j<size;j++){
		read_value[j]=read_value[j]/sum;
	}

}

void normalise(float *read_value,int size){
	float max=-1000;
	float min=1000;
	for(int i=0;i<size;i++){
		if(read_value[i]>max) max=read_value[i];
		if(read_value[i]<min) min=read_value[i];
	}
	float dis=max-min;
	//cout<<dis<<endl;
	for(int i=0;i<size;i++){
		read_value[i]=(read_value[i]-min)/dis;
	}
}







