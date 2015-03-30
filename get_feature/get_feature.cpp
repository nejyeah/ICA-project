#include<iostream>
#include<fstream>
#include<string>
#include"opencv/cv.h"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
extern "C"{
#include"cblas.h"
}
using namespace cv;
using namespace std;

//void sort1(float*,float*);
void sort2(float* w1,float* sort_w1,int index,int filter,int row,int input_channel,int hidden_channel,int hidden_block,int block1);
void storeImage2(float* out,int index,int relate_size,int input_channel,int hidden_block,string path,int picture_row,int picture_col);
void storeImage(float *Weight,int input,int input_channel,int filter,int hidden_block,string outpath,int picture_row,int picture_col);
void storeImage_onemap(float *Weight,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,string outpath);
void change_size(float *Weight,float *Weight_full,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,int input_row);
void normalization(float* w,int filter,int input_channel,int size_w);
void loadlayer3();
void loadlayer2();
void loadlayer1();

int main(){
	//loadlayer1();
	loadlayer2();
	//loadlayer3();
	return 0;
}

void loadlayer1(){
	//minist1
		
		string w_file="minist1_w_t1.dat";
		//string outpath1="./minist1_feature_t1/";
		string outpath1="./minist1_feature_t1/";
		int input_channel=1;
		int hidden_channel=3;
		int filter=10;
		int hidden_block=2*2*3;
		int input=28;
		int block_row=(input-filter)/2+1;
		int picture_row=4*input_channel;
		int picture_col=hidden_channel;

	//minist2

	/*
	   string w_file="minist2_w_t3.dat";
	   string outpath1="./minist2_t8/";
	//string outpath2="./minist2_t6_map/";
	int input_channel=3;
	int hidden_channel=3;
	int filter=10;
	int hidden_block=2*2*3;
	int input=20;
	int block_row=(input-filter)/2+1;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;
	*/

	//mnist3
	/*
	string w_file="minist3_w_t3.dat";
	string outpath1="./minist3_t1/t3_";
	//string outpath2="./minist2_t6_map/";
	int input_channel=3;
	int hidden_channel=3;
	int filter=10;
	int hidden_block=2*2*3;
	int input=12;
	int block_row=(input-filter)/2+1;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;
	*/
	//stl1
	
	/*
	string w_file="first_w_t2.dat";
	string outpath1="./l1_feature_t4/30";
	int input_channel=1;
	int hidden_channel=3;
	int filter=10;
	int hidden_block=2*2*3;
	int input=96;
	int block_row=(input-filter)/2+1;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;
*/
	int block_number=block_row*block_row;
	int size_w=hidden_block*block_number*filter*filter*input_channel;
	float* w=new float[size_w];
	ifstream fp(w_file.c_str(),ios::in|ios::binary);
	fp.read((char*)w,size_w*sizeof(float));
	fp.close();
	//storeImage(w,input,input_channel,filter,hidden_block,outpath1,picture_row,picture_col);
	storeImage_onemap(w,block_row,input_channel,filter,hidden_block,hidden_channel,outpath1);
}

void loadlayer2(){
	//stl
	/*	
		string w_file1="first_w_t1.dat";
		string w_file2="second_w_t1.dat";
		string outpath1="./l2_feature_t1/";
		int filter=10;
		int input_channel=3;
		int hidden_channel=8;
		int hidden_block=2*2*8;
		int block1=44;
	//第二层block数量40*40,不显示全部
	int block2=40;
	int block_number=40;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;

*/	   

	//minist

	string w_file1="minist1_w_t1.dat";
	string w_file2="minist2_w_t1.dat";
	string outpath1="./minist2_feature_t1/";
	string outpath2="./minist2_feature_t1/";
	int filter=10;
	int input_channel=1;
	int hidden_channel=3;
	int hidden_block=2*2*3;
	int layer2_input=20;
	//第一层block数量的row
	int block1=10;
	//第二层block数量的row
	int block2=6;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;
	int relate_size_l2=filter*2-2;

	int size_w1=block1*block1*hidden_block*filter*filter*input_channel;
	int size_sort_w1=filter*filter*hidden_channel*relate_size_l2*relate_size_l2*input_channel;
	int size_w2_block=hidden_block*filter*filter*hidden_channel;
	int size_w2=block2*block2*size_w2_block;
	int size_w2_feature_block=hidden_block*relate_size_l2*relate_size_l2*input_channel;
	int size_w2_feature=block2*block2*size_w2_feature_block;

	float* w1=new float[size_w1];
	float* sort_w1=new float[size_sort_w1];
	float* w2=new float[size_w2];
	float* w2_feature=new float[size_w2_feature];

	ifstream fp1(w_file1.c_str(),ios::in|ios::binary);
	fp1.read((char*)w1,size_w1*sizeof(float));
	fp1.close();
	ifstream fp2(w_file2.c_str(),ios::in|ios::binary);
	fp2.read((char*)w2,size_w2*sizeof(float));
	fp2.close();

	for(int i=0;i<block2*block2;i++){
		sort2(w1,sort_w1,i,filter,filter,input_channel,hidden_channel,hidden_block,block1);
		int M=hidden_block;
		int K=filter*filter*hidden_channel;
		int N=relate_size_l2*relate_size_l2*input_channel;
		cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,&w2[i*size_w2_block],K,sort_w1,N,0,&w2_feature[i*size_w2_feature_block],N);
		//store in a 4*3 little map
		//storeImage2(&w2_feature[i*size_w2_feature_block],i,relate_size_l2,input_channel,hidden_block,outpath1,picture_row,picture_col);
	}
	//store in a onemap
	storeImage_onemap(w2_feature,block2,input_channel,relate_size_l2,hidden_block,hidden_channel,outpath2);

	delete[] w1;
	delete[] w2;
	delete[] sort_w1;
	delete[] w2_feature;

}

void loadlayer3(){
	//stl
	/*	
		string w_file1="first_w_t1.dat";
		string w_file2="second_w_t1.dat";
		string w_file3="third_w_t1.dat";
		string path="./l3_feature_t1/";
		int filter=10;
		int input_channel=3;
		int hidden_channel=8;
		int hidden_block=2*2*8;
		int block1=44;
		int picture_row=4*input_channel;
		int picture_col=hidden_channel;
		*/ 

	//minist

	string w_file1="minist1_w_t1.dat";
	string w_file2="minist2_w_t3.dat";
	string w_file3="minist3_w_t3.dat";
	string outpath2="./minist3_feature_t3/l2_";
	string outpath21="./minist3_feature_t3/l2_f";
	string outpath3="./minist3_feature_t3/l3_";
	int filter=10;
	int input_channel=1;
	int hidden_channel=3;
	int hidden_block=2*2*3;
	
	int layer1_input=28;
	int layer2_input=20;
	int layer3_input=12;

	int block1=10;
	int block2=6;
	int block3=2;
	int picture_row=4*input_channel;
	int picture_col=hidden_channel;

	int relate_size_l1=filter;
	//the size of input related to a h2 block
	int relate_size_l2=relate_size_l1+filter-2;
	//the size of input related to a h3 block
	int relate_size_l3=relate_size_l2+filter-2;

	int size_w1=block1*block1*hidden_block*filter*filter*input_channel;
	int size_sort_w1=filter*filter*hidden_channel*relate_size_l2*relate_size_l2*input_channel;
	int size_w2_block=hidden_block*filter*filter*hidden_channel;
	int size_w2=block2*block2*size_w2_block;
	int size_w2_feature_block=hidden_block*relate_size_l2*relate_size_l2*input_channel;
	int size_w2_feature=block2*block2*size_w2_feature_block;
	int size_w2_feature_full=block2*block2*hidden_block*layer1_input*layer1_input*input_channel;
	int size_sort_w2_feature=filter*filter*hidden_channel*relate_size_l3*relate_size_l3*input_channel;
	int size_w3_block=hidden_block*filter*filter*hidden_channel;
	int size_w3=block3*block3*size_w3_block;
	int size_w3_feature_block=hidden_block*relate_size_l3*relate_size_l3*input_channel;
	int size_w3_feature=block3*block3*size_w3_feature_block;


	float* w1=new float[size_w1];
	float* sort_w1=new float[size_sort_w1];
	float* w2=new float[size_w2];
	float* w2_feature=new float[size_w2_feature];
	float* w2_feature_full=new float[size_w2_feature_full];
	float* sort_w2_feature=new float[size_sort_w2_feature];
	float* w3=new float[size_w3];
	float* w3_feature=new float[size_w3_feature];

	ifstream fp1(w_file1.c_str(),ios::in|ios::binary);
	fp1.read((char*)w1,size_w1*sizeof(float));
	fp1.close();
	ifstream fp2(w_file2.c_str(),ios::in|ios::binary);
	fp2.read((char*)w2,size_w2*sizeof(float));
	fp2.close();
	ifstream fp3(w_file3.c_str(),ios::in|ios::binary);
	fp3.read((char*)w3,size_w3*sizeof(float));
	fp3.close();

	//normalization(w1,filter,input_channel,size_w1);
	//normalization(w2,filter,input_channel,size_w2);
	//normalization(w3,filter,input_channel,size_w3);

	for(int i=0;i<block2*block2;i++){
		sort2(w1,sort_w1,i,filter,relate_size_l1,input_channel,hidden_channel,hidden_block,block1);
		int M=hidden_block;
		int K=filter*filter*hidden_channel;
		int N=relate_size_l2*relate_size_l2*input_channel;
		cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,&w2[i*size_w2_block],K,sort_w1,N,0,&w2_feature[i*size_w2_feature_block],N);
		//store in a 4*3 little map
		//storeImage2(&w2_feature[i*size_w2_feature_block],i,relate_size_l2,input_channel,hidden_block,outpath1,picture_row,picture_col);
	}
	//store in a onemap
	//storeImage_onemap(w2_feature,block2,input_channel,relate_size_l2,hidden_block,hidden_channel,outpath2);
	//change_size(w2_feature,w2_feature_full,block2,input_channel,relate_size_l2,hidden_block,hidden_channel,layer1_input);
	//storeImage_onemap(w2_feature_full,block2,input_channel,layer1_input,hidden_block,hidden_channel,outpath21);
	
	for(int i=0;i<block3*block3;i++){
		sort2(w2_feature,sort_w2_feature,i,filter,relate_size_l2,input_channel,hidden_channel,hidden_block,block2);
		int M=hidden_block;
		int K=filter*filter*hidden_channel;
		int N=relate_size_l3*relate_size_l3*input_channel;
		cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,1,&w3[i*size_w3_block],K,sort_w2_feature,N,0,&w3_feature[i*size_w3_feature_block],N);
		//storeImage2(&w3_feature[i*size_w3_feature_block],i,relate_size_l3,input_channel,hidden_block,outpath3,4,3);
	}
	//store in one map
	storeImage_onemap(w3_feature,block3,input_channel,relate_size_l3,hidden_block,hidden_channel,outpath3);

	delete[] w1;
	delete[] w2;
	delete[] sort_w1;
	delete[] w2_feature;
	delete[] w2_feature_full;
	delete[] sort_w2_feature;
	delete[] w3;
	delete[] w3_feature;

}
void sort2(float* w1,float* sort_w1,int index,int filter,int row,int input_channel,int hidden_channel,int hidden_block,int block1){
	int relative_blocknumber=filter/2*filter/2;
	int relative_blockrow=filter/2;
	int relative_row=filter+row-2;
	int block2=block1-filter/2+1;
	for(int i=0;i<relative_blocknumber;i++){
		int row_block=(index%block2)+(i%relative_blockrow);//4
		int col_block=(index/block2)+(i/relative_blockrow);//3
		int block_index=col_block*block1+row_block;//3*39+4=121
		int p=0;
		for(int j=0;j<hidden_block;j++){
			for(int k=0;k<row*row*input_channel;k++){
				// i 34 j 0 k 0
				int row_channel=j/4;//0
				int row_row=(i%relative_blockrow)*2+(j%4)%2;//8
				int row_col=(i/relative_blockrow)*2+(j%4)/2;//6
				int row_index=row_channel*filter*filter+row_col*filter+row_row;//128
				int col_channel=k/(row*row);//0
				int col_row=(i%relative_blockrow)*2+(k%(row*row))%row;//8
				int col_col=(i/relative_blockrow)*2+(k%(row*row))/row;//6
				int col_index=col_channel*relative_row*relative_row+col_col*relative_row+col_row;//6*38+8=236
				//cout<<"i:"<<i<<"\tj:"<<j<<"\tk:"<<k<<endl;
				//cout<<"\t\t"<<row_index*38*38*3+col_index<<"\t"<<block_index*2*2*8*20*20*3+p<<endl;
				int index_sort_w1=row_index*relative_row*relative_row*input_channel+col_index;
				sort_w1[index_sort_w1]=w1[block_index*hidden_block*row*row*input_channel+p];
				p++;
			}
		}
	}
}

void storeImage2(float* out,int index,int relate_size,int input_channel,int hidden_block,string path,int picture_row,int picture_col){
	int size=relate_size;
	int number=hidden_block;
	for(int i=0;i<number*input_channel;i++){
		float max=-1000;
		float min=1000;
		int zero_count=0;
		for(int j=0;j<size*size;j++){
			if(out[i*size*size+j]>max) max=out[i*size*size+j];
			if(out[i*size*size+j]<min) min=out[i*size*size+j];
			if(out[i*size*size+j]==0) zero_count++;
		}
		//cout<<"i:"<<i<<"\tzero_count:"<<zero_count<<endl;
		float dis=max-min;
		for(int j=0;j<size*size;j++){
			if(dis!=0){ 
				out[i*size*size+j]=(out[i*size*size+j]-min)/dis;
			}
		}
	}
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	Mat dispImg;
	dispImg.create((size+1)*picture_row-1,(size+1)*picture_col-1,CV_8UC1);
	vector<Mat> feature(1);
	for(int i=0;i<picture_col;i++){
		for(int j=0;j<picture_row;j++){
			Mat tmp(size,size,CV_8U);
			for(int m=0;m<size;m++){
				for(int n=0;n<size;n++){
					tmp.at<uchar>(n,m)=out[i*size*size*picture_row+j*size*size+m*size+n]*255;
				}
			}
			Mat imgROI(dispImg,Rect(i*(size+1),j*(size+1),size,size));
			feature[0]=tmp;
			merge(feature,imgROI);
			//Mat roi(display,Rect(m*(w+1),n*(h+1),w,h));
			//resize(tmp,imgROI,Size(size,size));
		}
	}
	stringstream stream1;
	stream1<<index;
	string name=path+"block_"+stream1.str()+".png";
	imwrite(name,dispImg);
	/*
	   string windowname="l2_f_"+stream2.str();
	   namedWindow(windowname,WINDOW_NORMAL);
	   imshow(windowname,dispImg);
	   waitKey();
	   destroyWindow(windowname);*/

}

void storeImage(float *Weight,int input,int input_channel,int filter,int hidden_block,string outpath,int picture_row,int picture_col){
	int block_number=((input-filter)/2+1)*((input-filter)/2+1);
	int size_w=hidden_block*block_number*filter*filter*input_channel;
	int size_feature=filter*filter;
	int size_picture=size_feature*picture_row*picture_col;
	int number_feature=size_w/size_feature;
	int number_picture=size_w/size_picture;

	for(int m=0;m<number_feature;m++){
		float min_w=10000;
		float max_w=-10000;
		int index=m*size_feature;
		for(int i=0;i<size_feature;i++){
			if(Weight[index+i]<min_w) min_w=Weight[index+i];
			if(Weight[index+i]>max_w) max_w=Weight[index+i];
		}
		float dis=max_w-min_w;
		for(int i=0;i<size_feature;i++){
			Weight[index+i]=(Weight[index+i]-min_w)/dis;
		}
	}
	//store picture
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	int show_picture_number=number_picture;
	if(number_picture>200) show_picture_number=200;
	for(int i=0;i<show_picture_number;i++){
		Mat display;
		int w=filter;
		int h=filter;
		display.create((h+1)*picture_row-1,(w+1)*picture_col-1,CV_8UC1);

		vector<Mat> feature(1);
		for(int m=0;m<picture_col;m++){
			for(int n=0;n<picture_row;n++){
				Mat roi(display,Rect(m*(w+1),n*(h+1),w,h));
				Mat f(w,h,CV_8UC1,Scalar(0));
				//Mat f1(w,h,CV_8UC1,Scalar(0));
				//Mat f2(w,h,CV_8UC1,Scalar(0));
				int start_index=i*size_picture+(m*picture_row+n)*size_feature;
				for(int k=0;k<w;k++){
					for(int l=0;l<h;l++){
						float weight=Weight[start_index+k*h+l];
						//float weight1=Weight[start_index+k*h+l+size_feature];
						//float weight2=Weight[start_index+k*h+l+size_feature*2];
						f.at<unsigned char>(k,l)=(unsigned char)(weight*255.0);
						//f1.at<unsigned char>(k,l)=(unsigned char)(weight1*255.0);
						//f2.at<unsigned char>(k,l)=(unsigned char)(weight2*255.0);
					}
				}
				feature[0]=f;
				//feature[1]=f1;
				//feature[2]=f2;
				merge(feature,roi);
			}
		}
		stringstream stream;
		stream<<i;
		string pngName;
		pngName=outpath+stream.str()+".png";
		imwrite(pngName,display);
	}
}

void storeImage_onemap(float *Weight,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,string outpath){
	int size_w=hidden_block*block_row*block_row*filter*filter*input_channel;
	int size_w_block=hidden_block*filter*filter*input_channel;
	int size_feature=filter*filter*input_channel;

	int number_feature=size_w/size_feature;
	int number_picture=hidden_channel;

	int picture_col=2*block_row;
	int picture_row=picture_col;

	for(int m=0;m<number_feature;m++){
		float min_w=10000;
		float max_w=-10000;
		int index=m*size_feature;
		for(int i=0;i<size_feature;i++){
			//if(m==0) cout<<i<<":"<<Weight[index+i]<<endl;
			if(Weight[index+i]<min_w) min_w=Weight[index+i];
			if(Weight[index+i]>max_w) max_w=Weight[index+i];
		}
		float dis=max_w-min_w;
		for(int i=0;i<size_feature;i++){

			Weight[index+i]=(Weight[index+i]-min_w)/dis;
			//if(m==0) cout<<i<<":"<<Weight[index+i]<<endl;
		}
	}
	//store picture
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	for(int i=0;i<number_picture;i++){
		Mat display;
		int w=filter;
		int h=filter;
		if(input_channel==1) display.create((h+1)*picture_row-1,(w+1)*picture_col-1,CV_8UC1);
		else display.create((h+1)*picture_row-1,(w+1)*picture_col-1,CV_8UC3); 

		vector<Mat> feature(input_channel);
		for(int m=0;m<picture_col;m++){
			for(int n=0;n<picture_row;n++){
				Mat roi(display,Rect(m*(w+1),n*(h+1),w,h));
				Mat f(w,h,CV_8UC1,Scalar(0));
				int block_index=(m/2)*block_row+n/2;
				int w_block_row=(m%2)*2+n%2+i*4;
				int start_index=block_index*size_w_block+w_block_row*size_feature;
				for(int ch=0;ch<input_channel;ch++){
					for(int k=0;k<w;k++){
						for(int l=0;l<h;l++){
							float weight=Weight[start_index+ch*w*h+k*h+l];
							f.at<unsigned char>(k,l)=(unsigned char)(weight*255.0);
						}
					}
					feature[input_channel-ch-1]=f;
				}
				merge(feature,roi);
			}
		}
		stringstream stream;
		stream<<i;
		string pngName;
		pngName=outpath+stream.str()+".png";
		imwrite(pngName,display);
	}

}
void storeImage_onemap1(float *Weight,int input_channel,int input_row,int input_col,int picture_row,int picture_col,int hidden_channel,string outpath){
	int size_feature=input_row*input_col*input_channel;
	int size_picture=size_feature*picture_row*picture_col;
	int number_picture=hidden_channel;
	int number_feature=picture_row*picture_col*hidden_channel;

	for(int m=0;m<number_feature;m++){
		float min_w=10000;
		float max_w=-10000;
		int index=m*size_feature;
		for(int i=0;i<size_feature;i++){
			if(Weight[index+i]<min_w) min_w=Weight[index+i];
			if(Weight[index+i]>max_w) max_w=Weight[index+i];
		}
		float dis=max_w-min_w;
		for(int i=0;i<size_feature;i++){

			Weight[index+i]=(Weight[index+i]-min_w)/dis;
		}
	}
	//store picture
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);

	for(int i=0;i<number_picture;i++){
		Mat display;
		int w=input_row;
		int h=input_col;
		if(input_channel==1) display.create((h+1)*picture_row-1,(w+1)*picture_col-1,CV_8UC1);
		else display.create((h+1)*picture_row-1,(w+1)*picture_col-1,CV_8UC3); 

		vector<Mat> feature(input_channel);
		for(int m=0;m<picture_col;m++){
			for(int n=0;n<picture_row;n++){
				Mat roi(display,Rect(m*(w+1),n*(h+1),w,h));
				Mat f(w,h,CV_8UC1,Scalar(0));
				int start_index=i*size_picture+(m*picture_row+n)*size_feature;
				for(int ch=0;ch<input_channel;ch++){
					for(int k=0;k<w;k++){
						for(int l=0;l<h;l++){
							float weight=Weight[start_index+ch*w*h+k*h+l];
							f.at<unsigned char>(k,l)=(unsigned char)(weight*255.0);
						}
					}
					feature[input_channel-ch-1]=f;
				}
				merge(feature,roi);
			}
		}
		stringstream stream;
		stream<<i;
		string pngName;
		pngName=outpath+stream.str()+".png";
		imwrite(pngName,display);
	}

}

void change_size(float *Weight,float *Weight_full,int block_row,int input_channel,int filter,int hidden_block,int hidden_channel,int input_row){
	int size_w=hidden_block*block_row*block_row*filter*filter*input_channel;
	int size_w_full=hidden_block*block_row*block_row*input_row*input_row*input_channel;
	int size_w_block=hidden_block*filter*filter*input_channel;
	int size_w_full_block=hidden_block*input_row*input_row*input_channel;
	int size_feature=filter*filter*input_channel;
	int size_feature_full=input_row*input_row*input_channel;

	int number_feature=size_w/size_feature;

	for(int m=0;m<size_w_full;m++){
		Weight_full[m]=0;
	}
	for(int i=0;i<number_feature;i++){
		int block_id=i/hidden_block;
		int r_block_row=block_id%block_row;
		int r_block_col=block_id/block_row;
		for(int j=0;j<size_feature;j++){
			int channel=j/(filter*filter);
			int row=(j%(filter*filter))%filter;
			int col=(j%(filter*filter))/filter;
			int real_row=r_block_row*2+row;
			int real_col=r_block_col*2+col;
			int index_w=i*size_feature+j;
			int index_w_full=i*size_feature_full+channel*input_row*input_row+real_col*input_row+real_row;
			Weight_full[index_w_full]=Weight[index_w];
		}
	}

}

void normalization(float* w,int filter,int input_channel,int size_w){
	int size_feature=filter*filter*input_channel;
	int number_feature=size_w/size_feature;
	for(int i=0;i<number_feature;i++){
		int index=i*size_feature;
		float sum=0;
		for(int j=0;j<size_feature;j++){
			sum+=w[index+j]*w[index+j];
		}
		for(int j=0;j<size_feature;j++){
			w[index+j]=w[index+j]/sum;
		}

	}
}
