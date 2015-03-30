#include<iostream>
#include<fstream>
#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void storeImage(float *,int ,int);
void showImage(float *,int ,int,int);

int main(){
	float *w;
	int picture=28;
	int filter=10;
	int channel=1;
	int size_w=2*2*8*((picture-filter)/2+1)*((picture-filter)/2+1)*filter*filter*channel;
	//int size_feature=filter*filter*3;

	w=new float[size_w];
	ifstream fp("minist_w_t.dat",ios::in|ios::binary);
	fp.read((char*)w,sizeof(float)*size_w);
	fp.close();

	showImage(w,picture,channel,filter);

	//storeImage(w,picture,filter);

	delete[] w;
	return 0;
}

void showImage(float *Weight,int picture,int channel,int filter){

	int size_feature=filter*filter;
	int size_picture=filter*filter;
	//int size_w=2*2*8*((picture-filter)/2+1)*((picture-filter)/2+1)*filter*filter*3;
	int number_picture=2*2*8*((picture-filter)/2+1)*((picture-filter)/2+1); 
	for(int i=0;i<number_picture*channel;i++){
		float min=1000;
		float max=-1000;
		for(int j=0;j<size_feature;j++){
			if(Weight[i*size_picture+j]<min) min=Weight[i*size_feature+j];
			if(Weight[i*size_picture+j]>max) max=Weight[i*size_feature+j];
		}
		cout<<"min:"<<min<<endl;
		cout<<"max:"<<max<<endl;
		float dis=max-min;
		Mat f1(filter,filter,CV_8UC1,Scalar(0));
		//Mat f2(filter,filter,CV_8UC1,Scalar(0));
		//Mat f3(filter,filter,CV_8UC1,Scalar(0));
		//Mat f4(filter,filter,CV_8UC1,Scalar(0));
		for(int col=0;col<filter;col++){
			for(int row=0;row<filter;row++){
				int index=col*filter+row;
				f1.at<unsigned char>(row,col)=(unsigned char)((Weight[i*size_picture+index]-min)/dis*255);
				//f2.at<unsigned char>(row,col)=(unsigned char)((Weight[i*size_picture+index+400]-min)/dis*255);
				//f3.at<unsigned char>(row,col)=(unsigned char)((Weight[i*size_picture+index+800]-min)/dis*255);
				//float tem=(Weight[i*size_picture+index]+Weight[i*size_picture+index+400]+Weight[i*size_picture+index+800])/3;
				//f4.at<unsigned char>(row,col)=(unsigned char)((tem-min)/dis*255);
			}
		}
		namedWindow("1",CV_WINDOW_NORMAL);
		resizeWindow("1",filter,filter);
		//namedWindow("2",CV_WINDOW_NORMAL);
		//namedWindow("3",CV_WINDOW_NORMAL);
		//namedWindow("4",CV_WINDOW_NORMAL);
		//resizeWindow("1",filter,filter);
		//resizeWindow("2",filter,filter);
		//resizeWindow("3",filter,filter);
		//resizeWindow("4",filter,filter);
		imshow("1",f1);
		//imshow("2",f2);
		//imshow("3",f3);
		//imshow("4",f4);
		waitKey();


	}
}

void storeImage(float *Weight,int picture,int filter){
	int size=39;
	int size_w=2*2*8*((picture-filter)/2+1)*((picture-filter)/2+1)*filter*filter*3;
	int size_feature=filter*filter;
	int size_picture=size_feature*size*size;
	int number_feature=size_w/size_feature;
	int number_picture=number_feature/(size*size);

	//store picture
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	for(int i=0;i<number_picture;i++){
		Mat grayImage;
		Mat display;
		int w=filter;
		int h=filter;
		display.create(h*size+size-1,w*size+size-1,CV_8UC1);

		vector<Mat> feature(1);
		for(int m=0;m<size;m++){
			for(int n=0;n<size;n++){
				Mat roi(display,Rect(m*(w+1),n*(h+1),w,h));
				Mat f(w,h,CV_8UC1,Scalar(0));
				int start_index=i*size_picture+(m*size+n)*size_feature;
				float min_w=10000;
				float max_w=-10000;
				for(int i=0;i<size_feature;i++){
					if(Weight[start_index+i]<min_w) min_w=Weight[start_index+i];
					if(Weight[start_index+i]>max_w) max_w=Weight[start_index+i];
				}
				cout<<"min:"<<min_w<<"\tmax:"<<max_w<<endl;
				float dis=max_w-min_w;

				for(int k=0;k<w;k++){
					for(int l=0;l<h;l++){
						f.at<unsigned char>(k,l)=(unsigned char)((Weight[start_index+k*h+l]-min_w)/dis*255);
					}
				}
				/*
				   namedWindow("w1",CV_WINDOW_NORMAL);
				   resizeWindow("w1",w,h);
				   imshow("w1",f);
				   waitKey();*/
				feature[0]=f;
				merge(feature,roi);
			}
		}
		stringstream stream;
		stream<<i;
		string pngName;
		pngName="./feature/layer1/"+stream.str()+".png";
		imwrite(pngName,display,compression_params);

	}

}
